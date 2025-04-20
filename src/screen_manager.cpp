#include "screen_manager.h"
#include "services/api/api.h"
#include "ui/popup.h"
#include "system/wifi_manager.h"

#include "screens/screen_pick_user.h"
#include "screens/screen_pick_resident.h"
#include "screens/screen_standby.h"
#include "screens/screen_transcription.h"
#include "screens/screen_display_extract.h"
#include "screens/screen_pick_record_type.h"

extern AppState appState;
extern MyApi api;

void changeScreen(Screen newScreen, bool addStuck) {
  if (appState.currentScreen != newScreen) {
    if(addStuck && appState.currentScreen != TRANSCRIPTION){
      appState.screenHistory.push(appState.currentScreen);
    }
    appState.currentScreen = newScreen;

    switch (newScreen) {
      case RESIDENT_PICKER:
        showResidentPickerScreen(appState);
        break;
      case STANDBY:
        api.setResidentUid(appState.selectedResident.residentUid);
        showStandbyScreen(appState);
        break;
      case TRANSCRIPTION:
        api.setRecordExtract(""); // 介護記録の初期化
        showTranscriptionScreen(appState);//これがレコーディングスタート関数
        break;
      case EXTRACT:
        appState.screenHistory = std::stack<Screen>(); // 履歴をクリア
        showRecordFromJson(appState, api.getRecordExtract());
        break;
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

void wifiDisconnectionPopup(){
  static bool isPopupVisible = false;
  bool isConnected = wifiDisconnectionObserve();

  if(!isConnected && !isPopupVisible){
    Serial.println("ネットワークから切断されました");
    showWifiDisconnectedPopup(appState);
    isPopupVisible = true;
  }

  if (isConnected && isPopupVisible) {
    Serial.println("ネットワークに再接続しました");
    isPopupVisible = false;
    showResidentPickerScreen(appState);
  }
}