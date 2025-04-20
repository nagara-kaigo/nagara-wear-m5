#include <M5Core2.h>
#include "loop.h"
#include "touch_handler.h"
#include "screen_manager.h"

void handleMainLoop() {
  M5.update();
  handleTouchEvents();
  wifiDisconnectionPopup();
}