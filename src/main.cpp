#include <M5Unified.h>
#include "setup.h"
#include "loop.h"
#include "task_manager.h"
#include "audio/audio_recorder.h"

AudioRecorder recorder; // グローバルインスタンス
File recordingFile;

void setup() {
  initializeSystem();
  recorder.initialize();  // ここで初期化
  //startBackgroundTasks();  // バックグラウンドタスクの起動
}

void loop() {
  handleMainLoop();
}
