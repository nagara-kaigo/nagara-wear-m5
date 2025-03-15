#include "task_manager.h"
#include "audio/audio_recorder.h"
#include "audio/audio_handler.h"
#include "system/wifi_manager.h"

void task0(void *parameter);
void task1(void *parameter);
//void task2(void *parameter);

void startBackgroundTasks() {
  xTaskCreatePinnedToCore(task0, "AudioTask", 16384, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(task1, "NetworkTask", 16384, NULL, 1, NULL, 1);
  //xTaskCreatePinnedToCore(task2, "ApiServerTask", 16384, NULL, 1, NULL, 1);
}

void task0(void *parameter) {
  while (true) {
    startRecording(); // 音声録音開始
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void task1(void *parameter) {
  while (true) {
    uploadAudioData();  // ネットワーク経由でデータ送信
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // 5秒ごとに送信
  }
}

/*
void task2(void *parameter) {
  while (true) {
    sendTranscriptionData();  // 文字起こしデータを送信
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1秒ごとに送信
  }
*/