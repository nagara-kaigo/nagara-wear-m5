#include <M5Core2.h>
#include "setup.h"
#include "config.h"
#include "screen_manager.h"
#include "system/sd_handler.h"
#include "system/wifi_manager.h"
#include "audio/audio_handler.h"
//#include "audio/audio_buffer.h"

AppState appState;

void initializeSystem() {
  M5.begin();
  M5.Lcd.setTextFont(4);
  M5.Lcd.setFreeFont(&unicode_24px);

  appState.currentScreen = USER_PICKER;
  showUserPickerScreen(appState);

  if (!initializeSD()) {
    Serial.println("SD Card init failed!");
    return;
  }

  connectToWiFi();
}