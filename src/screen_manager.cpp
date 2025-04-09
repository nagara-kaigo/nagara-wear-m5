#include "screen_manager.h"
#include "services/api/api.h"

extern AppState appState;
extern MyApi api;

void changeScreen(Screen newScreen, bool addStuck) {
  if (appState.currentScreen != newScreen) {
    if(addStuck){
      appState.screenHistory.push(appState.currentScreen);
    }
    appState.currentScreen = newScreen;

    switch (newScreen) {
      case RESIDENT_PICKER:
        showResidentPickerScreen(appState);
        break;
      case STANDBY:
        api.setresidentUid(appState.selectedResident.residentUid);
        showStandbyScreen(appState);
        break;
      case TRANSCRIPTION:
        showTranscriptionScreen(appState);//これがレコーディングスタート関数
        break;
      case EXTRACT:{
        String recordExtract = api.getRecordExtract();
        showRecordFromJson(recordExtract, appState);
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