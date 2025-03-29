#include "screen_manager.h"
#include "system/API.h"

extern AppState appState;
extern MyApi api;

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
      case MEAL_EXTRACT:{
        String mealExtract = api.getmealExtract();
        showMealRecordFromJson(mealExtract, appState);
        break;
      }
      case RECORD_TYPE_PICKER:
        showRecordTypeScreen(appState);
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