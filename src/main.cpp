#include <M5Core2.h>
#include "config.h"
//#include "recorder.h"
//#include "network.h"
//#include "openai.h"
#include "ui/header.h"
#include "ui/footer.h"
#include "screens/screen_pick_receiver.h"

AppState appState;

void setup() {
  M5.begin();
  appState.currentScreen = RECEIVER_PICKER;
  appState.selectedUser = String(DEFAULT_USER_UUID);
  showReceiverPickerScreen(appState);
  //showFooterBar(appState);
  //initRecorder();
  //initNetwork();
}

void loop() {
  M5.update();
  TouchPoint_t touch;

  if ( M5.Touch.ispressed() ) { // タッチされている場合
    touch = M5.Touch.getPressPoint();
    switch (appState.currentScreen) {
      case RECEIVER_PICKER:
        if (handleReceiverPickerTouch(touch, appState)) {
          appState.currentScreen = FINAL_SCREEN;
          M5.Lcd.clear();
          showHeaderBar("final screen");
          showFooterBar(appState);
          M5.Lcd.setCursor(10,40);
          M5.Lcd.print("User: " + appState.selectedUser);
          M5.Lcd.print("\nReceiver: " + appState.selectedReceiver);
        }
        break;
      case FINAL_SCREEN:
        break;
    }
  }

  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
    appState.currentScreen = RECEIVER_PICKER;
    showReceiverPickerScreen(appState);
  }
  //recordAndSend();
  //delay(100);
}
