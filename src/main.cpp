#include <Arduino.h>
#include <M5Core2.h>
#include "config.h"
#include "recorder.h"
#include "network.h"
#include "openai.h"
#include "screens/screen_pick_receiver.h"

AppState appState;

void setup() {
  M5.begin();
  appState.currentScreen = RECEIVER_PICKER;
  appState.selectedUser = String(DEFAULT_USER_UUID);
  showReceiverPickerScreen(appState);
  //initRecorder();
  initNetwork();
}

void loop() {
  TouchPoint_t touch;

  if ( M5.Touch.ispressed() ) { // タッチされている場合
    touch = M5.Touch.getPressPoint();
    switch (appState.currentScreen) {
      case RECEIVER_PICKER:
        if (handleReceiverPickerTouch(touch, appState)) {
          appState.currentScreen = FINAL_SCREEN;
          M5.Lcd.clear();
          M5.Lcd.setCursor(10,10);
          M5.Lcd.print("User: " + appState.selectedUser);
          M5.Lcd.print("\nReceiver: " + appState.selectedReceiver);
        }
        break;
      case FINAL_SCREEN:
        break;
    }
  }
  //recordAndSend();
  delay(100);
}
