#include <M5Core2.h>
#include "setup.h"
#include "config.h"
#include "screen_manager.h"
#include "system/sd_handler.h"
#include "system/wifi_manager.h"
#include "audio/audio_recorder.h"
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
  
  initializeAudioRecorder();
  //initializeAudioBuffer();

  xTaskCreatePinnedToCore(task0, "Task0", 16384, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(task1, "Task1", 16384, NULL, 1, NULL, 1);
}