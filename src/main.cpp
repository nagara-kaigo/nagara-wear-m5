#include <M5Core2.h>
#include "setup.h"
#include "loop.h"
#include "task_manager.h"

void setup() {
  initializeSystem();
  startBackgroundTasks();  // バックグラウンドタスクの起動
}

void loop() {
  handleMainLoop();
}
