#include <M5Unified.h>
#include "loop.h"
#include "touch_handler.h"

void handleMainLoop() {
  M5.update();
  handleTouchEvents();
}