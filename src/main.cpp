#include <M5Core2.h>
#include "config.h"
//#include "recorder.h"
//#include "network.h"
//#include "openai.h"
#include "ui/header.h"
#include "ui/footer.h"
#include "screens/screen_pick_user.h"
#include "screens/screen_pick_receiver.h"
#include "screens/screen_standby.h"
#include "screens/screen_recording.h"

AppState appState;

void setup() {
  M5.begin();
  M5.Lcd.setTextFont(4);
  appState.currentScreen = USER_PICKER;
  //appState.selectedUser = String(DEFAULT_USER_UUID);
  showUserPickerScreen(appState);
  //initRecorder();
  //initNetwork();
}

void loop() {
  M5.update();
  TouchPoint_t touch;

  if ( M5.Touch.ispressed() ) { // タッチされている場合
    touch = M5.Touch.getPressPoint();
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
    } else {
      // Home button
      if (touch.x >= 109 && touch.x <=218) {
        M5.Axp.SetLDOEnable(3, true);
        delay(75);
        M5.Axp.SetLDOEnable(3, false);
        appState.currentScreen = USER_PICKER;
        showUserPickerScreen(appState);
      } else if (touch.x < 109) {
        M5.Axp.SetLDOEnable(3, true);
        delay(75);
        M5.Axp.SetLDOEnable(3, false);
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
