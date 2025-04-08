#include "api.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "general.h"


// コンストラクタ: APIのベースURLを設定
MyApi::MyApi(const String& baseUrl) : _baseUrl(baseUrl) {}

// ログイン
String MyApi::loginToApi(const String& ID, const String& password) {
  String jsonBody = "{ \"loginId\": \"" + ID + "\", \"password\": \"" + password + "\" }";
  return httpPostJson(*this, "/auth/login", jsonBody);
}

// テナント一覧ゲット
String MyApi::getTenants(const String& token) {
  return httpGet(*this, "/tenants");
}

//ログインユーザー情報ゲット
String MyApi::getMe(const String& token) {
    return httpGet(*this, "/auth/me");
  }

//チャット一覧ゲット
String MyApi::getChats(const String& token){
    return httpGet(*this, "/chats");
}

//テナントユーザ一覧を取得
String MyApi::getTenantResident(const String& token){
  return httpGet(*this, "/tenants/" + tenantUid + "/residents");
}

//レジデント作成
// MyApi.cpp

String MyApi::createResidents(const String& token,
  const String& familyName,
  const String& givenName,
  const String& familyNameFurigana,
  const String& givenNameFurigana,
  const String& dateOfBirth,
  const String& gender,
  const String& admissionDate) 
{
// 1) 送信するJSONボディを組み立てる
String jsonBody = "{";
jsonBody += "\"familyName\":\"" + familyName + "\",";
jsonBody += "\"givenName\":\"" + givenName + "\",";
jsonBody += "\"familyNameFurigana\":\"" + familyNameFurigana + "\",";
jsonBody += "\"givenNameFurigana\":\"" + givenNameFurigana + "\",";
jsonBody += "\"dateOfBirth\":\"" + dateOfBirth + "\",";
jsonBody += "\"gender\":\"" + gender + "\",";
jsonBody += "\"admissionDate\":\"" + admissionDate + "\"";
jsonBody += "}";

// 2) POSTリクエストを送る
return httpPostJson(*this, "/tenants/" + tenantUid + "/residents", jsonBody);
}
