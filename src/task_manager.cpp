#include "task_manager.h"
#include "services/whisper_client.h"

TaskHandle_t task0Handle = NULL;
TaskHandle_t task1Handle = NULL;

void task0(void *parameter);
void task1(void *parameter);

void startBackgroundTasks() {
    recorder.initialize();
    xTaskCreatePinnedToCore(task0, "AudioTask", 8192, NULL, 2, &task0Handle, 1);
    xTaskCreatePinnedToCore(task1, "NetworkTask", 4096, NULL, 1, &task1Handle, 1);
}

void stopBackgroundTasks() {
    recorder.stopRecording();

    if (task0Handle) {
        vTaskDelete(task0Handle);
        task0Handle = NULL;
    }
    if (task1Handle) {
        vTaskDelete(task1Handle);
        task1Handle = NULL;
    }
}

void task0(void *parameter) {
    while (true) {
        recorder.startRecording();
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        recorder.stopRecording();
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}

void task1(void *parameter) {
    while (true) {
        Serial.println("[task1] Transcribing audio");
        transcribeAudio();  // ネットワーク経由で送信
        Serial.println("[task1] Transcription complete");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}