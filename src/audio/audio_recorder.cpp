#include "audio_recorder.h"
#include <M5Core2.h>

AudioRecorder::AudioRecorder()
    : audioRingBuffer(nullptr), tempBuffer(nullptr), writeIndex(0), readIndex(0),
      ringBufferMutex(nullptr), recording(false), recordingTaskHandle(nullptr) {
    initialize();
}

AudioRecorder::~AudioRecorder() {
    if (audioRingBuffer) free(audioRingBuffer);
    if (tempBuffer) free(tempBuffer);
    if (ringBufferMutex) vSemaphoreDelete(ringBufferMutex);
}

void AudioRecorder::initialize() {
    audioRingBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    tempBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    ringBufferMutex = xSemaphoreCreateMutex();

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
        .bck_io_num = 12,
        .ws_io_num = 0,
        .data_out_num = -1,
        .data_in_num = 34
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);
    i2s_set_clk(I2S_PORT, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

void AudioRecorder::startRecording() {
    if (recording) return;
    recording = true;

    recordingFile = SD.open("/recording.pcm", FILE_WRITE);
    if (!recordingFile) {
        Serial.println("Failed to open file for recording");
        recording = false;
        return;
    }

    xTaskCreatePinnedToCore(recordTask, "AudioRecordTask", 4096, this, 1, &recordingTaskHandle, 1);
}

void AudioRecorder::stopRecording() {
    if (!recording) return;
    recording = false;

    if (recordingTaskHandle) {
        vTaskDelete(recordingTaskHandle);
        recordingTaskHandle = nullptr;
    }
    
    if (recordingFile) {
        recordingFile.close();
    }
}

bool AudioRecorder::isRecording() const {
    return recording;
}

void AudioRecorder::recordTask(void* param) {
    AudioRecorder* recorder = static_cast<AudioRecorder*>(param);
    size_t bytesRead;
    
    while (recorder->recording) {
        i2s_read(I2S_PORT, recorder->tempBuffer, BUFFER_SIZE, &bytesRead, portMAX_DELAY);
        
        if (bytesRead > 0) {
            recorder->recordingFile.write(recorder->tempBuffer, bytesRead);
        }
    }
    
    vTaskDelete(nullptr);
}
