#include "audio_recorder.h"
#include "../services/transcription/whisper_client.h"
#include "../services/api/api.h"
#include "../system/time_manager.h"
#include <M5Core2.h>
#include "../tools/json.h"
#include "../services/api/records/food_records.h"
#include "../services/api/records/bath_records.h"
#include "../services/api/records/elimination_records.h"
#include "../services/api/records/beverage_records.h"
#include "../services/api/records/daily_records.h"

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

void AudioRecorder::startRecording(AppState &state) {
    if (recording || recordingTaskHandle != nullptr) return;
    String recordedAt = getFormattedTime();
    String response;
    switch (state.selectedRecordType) {
    case MEAL:
        //食事記録作成
        response = createFoodRecord(
            api,
            recordedAt,
            "", // notes
            mealTimeToString(state.mealTime),
            0,                    // mainCoursePercentage
            0,                    // sideDishPercentage
            0,                    // soupPercentage
            "WATER",               // beverageType(WATER, TEE, OTHER)
            0                    // beverageVolume
        );
        break;
    
    case BATH:
        //入浴記録作成
        response = createBathRecord(
            api,
            recordedAt,
            "",                     // notes
            ""                      // bathMethod (例: BATH, SHOWER, etc)
        );
        break;

    case EXCRETION: 
        //排泄記録作成
        response = createEliminationRecord(
            api,
            recordedAt,
            "",                     // notes
            "",              // eliminationMethod (例: TOILET, BEDPAN, etc)
            false,                 // hasFeces
            false,                 // fecalIncontinence
            "",                    // fecesAppearance (例: NORMAL, LIQUID, etc)
            0,                     // fecesVolume
            false,                 // hasUrine
            false,                 // urineIncontinence
            "",                    // urineAppearance (例: NORMAL, CLOUDY, etc)
            0                      // urineVolume
        );
        break;
    case DRINK: 
        //飲水記録作成
        response = createBeverageRecord(
            api,
            recordedAt,
            "",                     // notes
            "WATER",               // beverageType (例: WATER, TEE, etc)
            0                      // volume
        );
        break;
    case EVERYDAY:
        //日常記録作成
        response = createDailyRecord(
            api,
            recordedAt,
            "",                     // notes
            "NORMAL"               // dailyStatus (例: NORMAL, WARNING, ALERT)
        );
        break;
    }
        
    Serial.println(recordedAt);
    Serial.println("CreateRecord response:");
    Serial.println(response);
    String recordUid = getJsonValue(response,"uid");
    Serial.println(recordUid);
    api.setRecordUid(recordUid);
    Serial.println(api.getRecordUid());
  
    recording = true;
    Serial.println("[task0] Recording start");
}

void AudioRecorder::stopRecording() {
    //String token  = api.getuserToken();
    //String mealInfo = api.mealRecordInfo();
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
    //Serial.println(mealInfo);
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
        
        int16_t* in      = reinterpret_cast<int16_t*>(buffer); 
        size_t   samples = bytesRead / 2;                       // 2 byte = 1 sample

        if (xSemaphoreTake(recorder->ringBufferMutex, 10 / portTICK_PERIOD_MS)) {
            for (size_t n = 0; n < samples; ++n) {

                int16_t pcm16 = in[n];

                recorder->audioRingBuffer[recorder->writeIndex]               = pcm16 & 0xFF;
                recorder->audioRingBuffer[(recorder->writeIndex + 1) % BUFFER_SIZE] = pcm16 >> 8;

                recorder->writeIndex = (recorder->writeIndex + 2) % BUFFER_SIZE;
            }
            xSemaphoreGive(recorder->ringBufferMutex);
        }
    return;
    }
}