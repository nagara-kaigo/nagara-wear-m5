#include <M5Core2.h>
#include "setup.h"
#include "config.h"
#include "screen_manager.h"
#include "system/sd_handler.h"
#include "system/wifi_manager.h"
#include "system/time_manager.h"
//#include "audio/audio_buffer.h"
#include "services/api/api.h"
#include "tools/json.h"
#include <WiFiClientSecure.h>
#include "services/api/residents.h"
#include <vector>
#include "screens/screen_roading.h"

AppState appState;

MyApi api;  // `MyApi` クラスのインスタンスを作成

// **HTTP リクエストの送信**
WiFiClientSecure client;

void initializeSystem() {
  //M5スタックイニシャライズ
  M5.begin();
  M5.Axp.SetLDOEnable(2, true);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setFreeFont(&unicode_24px);

  appState.currentScreen = RESIDENT_PICKER;
  appState.screenHistory.push(appState.currentScreen);

  showRoadingScreen(appState);
  

  //SDカード初期化
  if (!initializeSD()) {
    Serial.println("SD Card init failed!");
    M5.Lcd.drawString("メモリーカードが確認できませんでした", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
    return;
  }
  M5.Lcd.drawString("メモリーカードを確認しました", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
  //Wi-Fi接続
  connectToWiFi();
  client.setInsecure();  // SSL 証明書の検証を無効化
  M5.Lcd.setTextDatum(MC_DATUM);
  // 現在時刻取得
  initializeTime();
  //ログイン
  String loginResponse = api.loginToApi(API_LOGIN_ID, API_PASSWORD);
  Serial.println("Login Response:");
  Serial.println(loginResponse);
  String token = getJsonValue(loginResponse,"token");
  api.setuserToken(token);
  //ユーザ情報獲得
  String userinfo = api.getMe(token);
  Serial.println("userinfo:");
  Serial.println(userinfo);
  String tenantUid = getJsonValue(userinfo,"tenantUid");
  api.settenantUid(tenantUid);
  Serial.println(tenantUid);
  //テナントレジデント一覧取得
  String tenantResidents = getTenantResidents(api,token);
  Serial.println("tenantUser:");
  Serial.println(tenantResidents);
  //抽出する値の設定
  std::vector<String> fields = { "uid", "familyName", "givenName"};
  appState.residentsList = getValueAllInJson(tenantResidents,"items",fields);
  // シリアルで中身を表示する例
  Serial.println("=== Residents List ===");

  for (size_t i = 0; i < appState.residentsList.size(); i++) {
    Serial.print("[" + String(i) + "] uid: ");
    Serial.println(appState.residentsList[i].residentUid);

    Serial.print("        familyName: ");
    Serial.println(appState.residentsList[i].familyName);

    Serial.print("        givenName : ");
    Serial.println(appState.residentsList[i].givenName);

    Serial.println("----------------------");
  }
  //api.setresidentUid(residentUid);
  //Serial.println(residentUid);
  //テナントレジデント作成
  /*
  String result = createResident(
    api,
    token, 
    "赤松",          // familyName
    "大和",          // givenName
    "アカマツ",        // familyNameFurigana
    "ヤマト",        // givenNameFurigana
    "2003-11-19",    // dateOfBirth
    "MALE",          // gender
    "2025-04-02"     // admissionDate一輝一輝
  );

  // 結果確認
  Serial.println("CreateResidents response:");
  Serial.println(result);
  */


  showResidentPickerScreen(appState);

}