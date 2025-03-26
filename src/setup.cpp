#include <M5Core2.h>
#include "setup.h"
#include "config.h"
#include "screen_manager.h"
#include "system/sd_handler.h"
#include "system/wifi_manager.h"
//#include "audio/audio_buffer.h"
#include "system/API.h"

AppState appState;

MyApi api;  // `MyApi` クラスのインスタンスを作成

void initializeSystem() {
  //M5スタックイニシャライズ
  M5.begin();
  M5.Axp.SetLDOEnable(2, true);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setFreeFont(&unicode_24px);

  appState.currentScreen = USER_PICKER;
  appState.screenHistory.push(appState.currentScreen);
  showUserPickerScreen(appState);

  //SDカード初期化
  if (!initializeSD()) {
    Serial.println("SD Card init failed!");
    return;
  }
  //Wi-Fi接続
  connectToWiFi();
  //ログイン
  String loginResponse = api.loginToApi("hardware-test", "password");
  Serial.println("Login Response:");
  Serial.println(loginResponse);
  String token = getJsonValue(loginResponse,"token");
  api.setuserToken(token);
  //ユーザ情報獲得
  String userinfo = api.get_Me(token);
  Serial.println("userinfo:");
  Serial.println(userinfo);
  String tenantUid = getJsonValue(userinfo,"tenantUid");
  api.settenantUid(tenantUid);
  Serial.println(tenantUid);
  //テナントレジデント一覧取得
  String tenantResident = api.get_tenantResident(token);
  Serial.println("tenantUser:");
  Serial.println(tenantResident);
  String residentUid = getValueInJson(tenantResident,"items","uid");
  api.setresidentUid(residentUid);
  Serial.println(residentUid);
  //テナントレジデント作成
  /*
  String result = api.CreateResidents(
    token, 
    "北村",          // familyName
    "虎汰朗",          // givenName
    "キタムラ",        // familyNameFurigana
    "コタロウ",        // givenNameFurigana
    "2004-12-19",    // dateOfBirth
    "MALE",          // gender
    "2025-03-25"     // admissionDate
  );

  // 結果確認
  Serial.println("CreateResidents response:");
  Serial.println(result);
  */


}