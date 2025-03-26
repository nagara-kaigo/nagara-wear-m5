#include "audio_recorder.h"
#include "../services/whisper_client.h"
#include "../system/API.h"
#include <M5Core2.h>

extern MyApi api;


AudioRecorder::AudioRecorder()
    : audioRingBuffer(nullptr), tempBuffer(nullptr), writeIndex(0), readIndex(0),
      ringBufferMutex(nullptr), recording(false), recordingTaskHandle(nullptr)
      {
        writeIndex = 0;
        readIndex = 0;
        audioRingBuffer = nullptr;
        tempBuffer = nullptr;
      }

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
    this->tempBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    audioRingBuffer = (uint8_t*)ps_malloc(BUFFER_SIZE);
    if (!audioRingBuffer) {
        Serial.println("Failed to allocate audioRingBuffer");
        while(1);  // メモリ確保失敗時は停止
        //return;
    }

    ringBufferMutex = xSemaphoreCreateMutex();
    if (!ringBufferMutex) {
        Serial.println("Failed to create mutex");
        free(audioRingBuffer);
        audioRingBuffer = nullptr;
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
    String token  = api.getuserToken();
    String residentUid = api.getResidentUid();
      //食事記録作成
  
    String response = api.CreateFoodRecord(
        token,
        residentUid,
        "2024-03-20T12:00:00Z", // recordedAt
        "ちょっと少なめに食べました", // notes
        "LUNCH",               // mealTime (例: LUNCH, DINNER, etc)
        80,                    // mainCoursePercentage
        70,                    // sideDishPercentage
        90,                    // soupPercentage
        "WATER",               // beverageType
        200                    // beverageVolume
    );
        
    Serial.println("CreateFoodRecord response:");
    Serial.println(response);
    String foodRecordUid = getJsonValue(response,"uid");
    api.setfoodRecordUid(foodRecordUid);

  
    recording = true;
    Serial.println("[task0] Recording start");
}

void AudioRecorder::stopRecording() {
    String token  = api.getuserToken();
    String mealInfo = api.mealRecordInfo();
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
    Serial.println(mealInfo);
}

void AudioRecorder::recordTask(void* param) {
    if (param == nullptr) {
        Serial.println("Error: recordTask received nullptr");
        vTaskDelete(nullptr);
        return;
    }
    uint8_t buffer[1024];  
    AudioRecorder* recorder = static_cast<AudioRecorder*>(param);
    size_t bytesRead;
    esp_err_t result = i2s_read(I2S_PORT, buffer, sizeof(buffer), &bytesRead, portMAX_DELAY);
    if (result == ESP_OK && bytesRead > 0) {
        /*
        for (int i = 0; i < 10&&bytesRead; i++) {
            Serial.printf("%02x ", buffer[i]);
        }
        recorder->recordingFile.write(buffer, bytesRead);
        */
        if (xSemaphoreTake(recorder->ringBufferMutex, (TickType_t)10) == pdTRUE) {
            for (size_t i = 0; i < bytesRead; i++) {
              recorder->audioRingBuffer[recorder->writeIndex] = buffer[i];
              recorder->writeIndex = (recorder->writeIndex + 1) % BUFFER_SIZE;
            }
            xSemaphoreGive(recorder->ringBufferMutex);
          }
    }

    //recorder->recording = false;
    //vTaskDelete(nullptr);
    return;
}