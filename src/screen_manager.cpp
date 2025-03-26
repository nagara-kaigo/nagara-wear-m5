#include "screen_manager.h"

extern AppState appState;

void changeScreen(Screen newScreen, bool addStuck) {
  if (appState.currentScreen != newScreen) {
    if(addStuck){
      appState.screenHistory.push(appState.currentScreen);
    }
    appState.currentScreen = newScreen;

    switch (newScreen) {
      case USER_PICKER:
        showUserPickerScreen(appState);
        break;
      case STANDBY:
        showStandbyScreen(appState);
        break;
      case RECORDING:
        showRecordingScreen(appState);
        break;
      case TRANSCRIPTION:
        showTranscriptionScreen(appState);//これがレコーディングスタート関数
        break;
    }
  }
}

void popScreen() {
  if (!appState.screenHistory.empty()) {
      Screen previous = appState.screenHistory.top();
      appState.screenHistory.pop();
      changeScreen(previous,false);
  }
}