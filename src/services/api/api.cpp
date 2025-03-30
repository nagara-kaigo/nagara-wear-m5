#include "api.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


// コンストラクタ: APIのベースURLを設定
MyApi::MyApi(const String& baseUrl) : _baseUrl(baseUrl) {}

// ログイン
String MyApi::loginToApi(const String& ID, const String& password) {
  String jsonBody = "{ \"loginId\": \"" + ID + "\", \"password\": \"" + password + "\" }";
  return httpPostJson("/auth/login", jsonBody);
}

// テナント一覧ゲット
String MyApi::getTenants(const String& token) {
  return httpGet("/tenants", token);
}

//ログインユーザー情報ゲット
String MyApi::getMe(const String& token) {
    return httpGet("/auth/me", token);
  }

//チャット一覧ゲット
String MyApi::getChats(const String& token){
    return httpGet("/chats", token);
}

//テナントユーザ一覧を取得
String MyApi::getTenantResident(const String& token){
  return httpGet("/tenants/" + tenantUid + "/residents", token);
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
return httpPostJson("/tenants/" + tenantUid + "/residents", jsonBody, token);
}









// HTTP POST リクエストの共通処理
String MyApi::httpPostJson(const String& endpoint, const String& jsonBody, const String& token) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  String url = _baseUrl + endpoint;
  String payload;

  if (http.begin(client, url)) {
    http.addHeader("Content-Type", "application/json");
    if (token.length() > 0) {
      http.addHeader("Authorization", "Bearer " + token);
    }

    int httpCode = http.POST(jsonBody);
    if (httpCode > 0) {
      payload = http.getString();
    } else {
      payload = "[HTTP] POST failed, error: " + String(http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    payload = "[HTTP] Unable to connect " + url;
  }

  return payload;
}

// HTTP GET リクエストの共通処理
String MyApi::httpGet(const String& endpoint, const String& token) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  String url = _baseUrl + endpoint;
  String payload;

  if (http.begin(client, url)) {
    if (token.length() > 0) {
      http.addHeader("Authorization", "Bearer " + token);
    }

    int httpCode = http.GET();
    if (httpCode > 0) {
      payload = http.getString();
    } else {
      payload = "[HTTP] GET failed, error: " + String(http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    payload = "[HTTP] Unable to connect " + url;
  }

  return payload;
}

//HTTP PATCHリクエストの共通処理
String MyApi::httpPatchJson(const String& endpoint, const String& jsonBody, const String& token) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  String payload;
  String url = _baseUrl + endpoint;
  if (!http.begin(client, url)) {
      payload = "[HTTP] Unable to connect " + url;
  }

  // ヘッダを付加
  http.addHeader("Content-Type", "application/json");
  if (token.length() > 0) {
      http.addHeader("Authorization", "Bearer " + token);
  }

  // PATCHリクエストを発行
  // sendRequest() 第1引数に "PATCH"
  int httpCode = http.sendRequest("PATCH", (uint8_t*)jsonBody.c_str(), jsonBody.length());
  if (httpCode > 0) {
      payload = http.getString();
  } else {
      payload = "[HTTP] PATCH failed, error: " + String(http.errorToString(httpCode).c_str());
  }

  http.end();
  return payload;
}

