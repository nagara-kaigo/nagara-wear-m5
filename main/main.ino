#include <M5Core2.h>
#include "config.h"
#include "recorder.h"
#include "network.h"
#include "openai.h"
#include "src/screens/screen_pick_receiver.h"

AppState appState;

Screen currentScreen = RECEIVER_PICKER;

void setup() {
  M5.begin();
  M5.Touch.begin();
  appState.selectedUser = String(DEFAULT_USER_UUID);
  showReceiverPickerScreen(appState);
  //initRecorder();
  initNetwork();
}

void loop() {
  M5.update();
  TouchPoint_t touch = M5.Touch.getPressPoint();

  if (touch.x != -1 && touch.y != -1) { // タッチされている場合
    switch (currentScreen) {
      case RECEIVER_PICKER:
        if (handleReceiverPickerTouch(touch, appState)) {
          currentScreen = FINAL_SCREEN;
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
  delay(50);
}
