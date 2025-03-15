#include <M5Core2.h>
#include "CUF_24px.h"
#include "config.h"
#include "ui/header.h"
#include "ui/footer.h"
#include "screens/screen_pick_user.h"
#include "screens/screen_pick_receiver.h"
#include "screens/screen_standby.h"
#include "screens/screen_recording.h"
#include "screens/screen_transcription.h"
#include "audio_recorder.h"
#include "sd_handler.h"
#include "whisper_client.h"
#include "wifi_manager.h"
#include "audio_buffer.h"

AppState appState;

void setup() {
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
  initializeAudioBuffer();

  xTaskCreatePinnedToCore(task0, "Task0", 16384, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(task1, "Task1", 16384, NULL, 1, NULL, 1);
}

void loop() {
  M5.update();
  TouchPoint_t touch;

  if ( M5.Touch.ispressed() ) { // タッチされている場合
    touch = M5.Touch.getPressPoint();
    // メインコンテンツのタッチ
    if (touch.y < 200) {
      switch (appState.currentScreen) {
        case USER_PICKER:
          if (handleUserPickerTouch(touch, appState)) {
            appState.currentScreen = STANDBY;
            showStandbyScreen(appState);
          }
          break;
        case STANDBY:
          if (handleRecBtnTouch(touch, appState)) {
            appState.currentScreen = RECORDING;
            showRecordingScreen(appState);
          }
          break;
      }
    // フッター部分のタッチ
    } else {
      // Home button
      if (touch.x >= 109 && touch.x <=218) {
        M5.Axp.SetLDOEnable(3, true);
        delay(75);
        M5.Axp.SetLDOEnable(3, false);
        appState.currentScreen = USER_PICKER;
        showUserPickerScreen(appState);
      // transcription button
      } else if (touch.x < 109) {
        M5.Axp.SetLDOEnable(3, true);
        delay(75);
        M5.Axp.SetLDOEnable(3, false);
        appState.currentScreen = TRANSCRIPTION;
        showTranscriptionScreen(appState);
      } else if (touch.x > 218) {
        M5.Axp.SetLDOEnable(3, true);
        delay(75);
        M5.Axp.SetLDOEnable(3, false);
      }
    }
  }


  //recordAndSend();
  //delay(10);
}
