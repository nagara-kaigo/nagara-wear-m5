#include "task_manager.h"
#include "services/whisper_client.h"
#include "audio/audio_recorder.h"
#include "screen_manager.h"
#include "system/API.h"
extern MyApi api;

TaskHandle_t task0Handle = NULL;
TaskHandle_t task1Handle = NULL;

void task0(void *parameter);
void task1(void *parameter);

void startBackgroundTasks() {
    xTaskCreatePinnedToCore(task0, "AudioTask", 32768, &recorder, 2, &task0Handle, 1);
    xTaskCreatePinnedToCore(task1, "NetworkTask", 32768, &recorder, 1, &task1Handle, 1);
}

void stopBackgroundTasks() {
    recorder.stopRecording();

}

void task0(void *parameter) {
    AudioRecorder* recorder = static_cast<AudioRecorder*>(parameter);
    recorder->startRecording();
    while(recorder->isRecording()){
        recorder->recordTask(parameter);
        vTaskDelay(pdMS_TO_TICKS(30));
    }
    Serial.println("task0 vTaskDelete");
    vTaskDelete(NULL);
}

void task1(void *parameter) {
    AudioRecorder* recorder = static_cast<AudioRecorder*>(parameter);
    while (true) {  
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        Serial.println("[task1] Transcribing audio");
        transcribeAudio();  // ネットワーク経由で送信
        Serial.println("[task1] Transcription complete");
        Serial.println(recorder->isRecording());
        //食事記録を取得
        String token  = api.getuserToken();
        String mealInfo = api.mealRecordInfo();
        Serial.println("After transcribe MealInfo is:");
        Serial.println(mealInfo);
        vTaskDelay(pdMS_TO_TICKS(30));
        if(!recorder->isRecording()){
            Serial.println("task1 vTaskDelete");
            changeScreen(STANDBY);
            vTaskDelete(NULL);
        }
    }
}