#include "general.h"
#include "api.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

extern MyApi api;
String accessToken = api.getuserToken();

bool httpPostJson(const String& url, const String& jsonBody) {
  HTTPClient https;
  https.begin(url);
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer " + accessToken);

  int httpCode = https.POST(jsonBody);
  String payload = https.getString();
  https.end();

  Serial.printf("POST %s\n%d\n%s\n", url.c_str(), httpCode, payload.c_str());
  return httpCode >= 200 && httpCode < 300;
}

bool httpPatchJson(const String& url, const String& jsonBody) {
  HTTPClient https;
  https.begin(url);
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer " + accessToken);

  int httpCode = https.sendRequest("PATCH", jsonBody);
  String payload = https.getString();
  https.end();

  Serial.printf("PATCH %s\n%d\n%s\n", url.c_str(), httpCode, payload.c_str());
  return httpCode >= 200 && httpCode < 300;
}

String httpGet(const String& url) {
  HTTPClient https;
  https.begin(url);
  https.addHeader("Authorization", "Bearer " + accessToken);

  int httpCode = https.GET();
  String payload = https.getString();
  https.end();

  Serial.printf("GET %s\n%d\n%s\n", url.c_str(), httpCode, payload.c_str());
  return (httpCode >= 200 && httpCode < 300) ? payload : "";
}

bool httpDelete(const String& url) {
  HTTPClient https;
  https.begin(url);
  https.addHeader("Authorization", "Bearer " + accessToken);

  int httpCode = https.sendRequest("DELETE");
  String payload = https.getString();
  https.end();

  Serial.printf("DELETE %s\n%d\n%s\n", url.c_str(), httpCode, payload.c_str());
  return httpCode >= 200 && httpCode < 300;
}

// ---- レコード共通関数 ----

bool createRecord(const String& baseUrl, const String& endpoint, const String& jsonBody) {
  return httpPostJson(baseUrl + endpoint, jsonBody);
}

bool patchRecord(const String& baseUrl, const String& endpoint, const String& recordUid, const String& jsonBody) {
  return httpPatchJson(baseUrl + endpoint + "/" + recordUid, jsonBody);
}

String getRecord(const String& baseUrl, const String& endpoint, const String& recordUid) {
  return httpGet(baseUrl + endpoint + "/" + recordUid);
}

bool deleteRecord(const String& baseUrl, const String& endpoint, const String& recordUid) {
  return httpDelete(baseUrl + endpoint + "/" + recordUid);
}