#include "task_manager.h"
#include "services/transcription/whisper_client.h"
#include "audio/audio_recorder.h"
#include "screen_manager.h"
#include "services/api/api.h"
#include "services/api/records.h"
extern MyApi api;
extern AppState appState;

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
    recorder->startRecording(appState);
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
        // 各記録を取得
        String token  = api.getUserToken();
        String recordInfo = fetchRecordInfo(api, appState.selectedRecordType);
        api.setRecordExtract(recordInfo);
        Serial.println("After transcribe info is:");
        Serial.println(recordInfo);
        vTaskDelay(pdMS_TO_TICKS(30));
        if(!recorder->isRecording()){
            Serial.println("task1 vTaskDelete");
            changeScreen(EXTRACT);
            vTaskDelete(NULL);
        }
    }
}