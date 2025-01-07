#include <M5Core2.h>
#include "recorder.h"
#include "network.h"
#include "openai.h"
#include "src/screens/screen_pick_user.h"
#include "src/screens/screen_pick_receiver.h"

enum Screen { USER_PICKER, RECEIVER_PICKER };
struct AppState {
  Screen currentScreen;
  String user;
  String receiver;
}
Screen currentScreen = USER_PICKER;

void setup() {
    M5.begin();
    showUserPickerScreen();
    initRecorder();
    initNetwork();
}

void loop() {
    switch (currentScreen) {
        case USER_PICKER:
            if (M5.BtnA.wasPressed()) {
                currentScreen = RECEIVER_PICKER;
                showReceiverPickerScreen();
            }
            break;
        case RECEIVER_PICKER:
            if (M5.BtnA.wasPressed()) {
                currentScreen = RECEIVER_PICKER;
                showUserPickerScreen();
            }
            break;
    }
    M5.update();
    recordAndSend();
    delay(1000);
}
