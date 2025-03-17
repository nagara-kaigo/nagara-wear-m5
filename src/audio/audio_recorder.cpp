#include "audio_recorder.h"

AudioRecorder::AudioRecorder()
    : audioRingBuffer(nullptr), tempBuffer(nullptr), writeIndex(0), readIndex(0),
      ringBufferMutex(nullptr), recording(false), recordingTaskHandle(nullptr) {}

AudioRecorder::~AudioRecorder() {
    if (audioRingBuffer) {
        free(audioRingBuffer);
        audioRingBuffer = nullptr;
    }
    if (tempBuffer) {
        free(tempBuffer);
        tempBuffer = nullptr;
    }
    if (ringBufferMutex) {
        vSemaphoreDelete(ringBufferMutex);
        ringBufferMutex = nullptr;
    }
}

void AudioRecorder::initialize() {
    audioRingBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    if (!audioRingBuffer) {
        Serial.println("Failed to allocate audioRingBuffer");
        while(1);  // メモリ確保失敗時は停止
        //return;
    }

    tempBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    if (!tempBuffer) {
        Serial.println("Failed to allocate tempBuffer");
        free(audioRingBuffer);  // 失敗時に確保済みメモリを解放
        audioRingBuffer = nullptr;
        while(1);  // メモリ確保失敗時は停止
        //return;
    }

    ringBufferMutex = xSemaphoreCreateMutex();
    if (!ringBufferMutex) {
        Serial.println("Failed to create mutex");
        free(audioRingBuffer);
        free(tempBuffer);
        audioRingBuffer = nullptr;
        tempBuffer = nullptr;
        return;
    }

    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 12,   // BCKピン
        .ws_io_num = 0,     // LRCKピン
        .data_out_num = -1, // 出力不要（録音のみ）
        .data_in_num = 34   // DINピン
      };

    i2s_driver_uninstall(I2S_PORT);  // 既存のI2Sドライバを削除
    esp_err_t err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        Serial.printf("I2S Driver install failed: %d\n", err);
        return;
    }

    //i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config); // 内蔵マイク使用
    i2s_set_clk(I2S_PORT, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

void AudioRecorder::startRecording() {
    if (recording || recordingTaskHandle != nullptr) return;
    recording = true;

    recordingFile = SD.open("/recording.pcm", FILE_WRITE);
    if (!recordingFile) {
        Serial.println("Failed to open file for recording");
        recording = false;
        return;
    }

    Serial.println("[task0] Recording start");
    xTaskCreatePinnedToCore(recordTask, "AudioRecordTask", 8192, this, 2, &recordingTaskHandle, 1);
}

void AudioRecorder::stopRecording() {
    if (!recording) return;
    recording = false; 

    if (recordingTaskHandle) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        vTaskDelete(recordingTaskHandle);
        recordingTaskHandle = nullptr;
    }

    if (recordingFile) {
        recordingFile.close();
    }

    Serial.println("[task0] Recording end");
}

void AudioRecorder::recordTask(void* param) {
    AudioRecorder* recorder = static_cast<AudioRecorder*>(param);
    size_t bytesRead;

    if (!recorder->tempBuffer) {
        Serial.println("Error: tempBuffer is NULL");
        recorder->recording = false;
        vTaskDelete(nullptr);
        return;
    }

    while (recorder->recording) {
        esp_err_t result = i2s_read(I2S_PORT, recorder->tempBuffer, BUFFER_SIZE, &bytesRead, portMAX_DELAY);

        if (result == ESP_OK && bytesRead > 0) {
            for (int i = 0; i < 10&&bytesRead; i++) {
                Serial.printf("%02x ", recorder->tempBuffer[i]);
            }
            recorder->recordingFile.write(recorder->tempBuffer, bytesRead);
        }
    }

    recorder->recording = false;
    vTaskDelete(nullptr);
    return;
}