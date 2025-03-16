#include "audio_recorder.h"

AudioRecorder::AudioRecorder()
    : audioRingBuffer(nullptr), tempBuffer(nullptr), writeIndex(0), readIndex(0),
      ringBufferMutex(nullptr), recording(false), recordingTaskHandle(nullptr) {}

AudioRecorder::~AudioRecorder() {
    if (audioRingBuffer) free(audioRingBuffer);
    if (tempBuffer) free(tempBuffer);
    if (ringBufferMutex) vSemaphoreDelete(ringBufferMutex);
}

void AudioRecorder::initialize() {
    /*
    M5.begin(); // M5Core2の初期化
    if (!SD.begin()) {
        Serial.println("SDカードの初期化に失敗しました");
        return;
    }
    */

    audioRingBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    tempBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    ringBufferMutex = xSemaphoreCreateMutex();

    if (!audioRingBuffer || !tempBuffer || !ringBufferMutex) {
        Serial.println("Memory allocation failed!");
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

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, NULL); // 内蔵マイク使用
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
            recorder->recordingFile.write(recorder->tempBuffer, bytesRead);
        }
    }

    vTaskDelete(nullptr);
}