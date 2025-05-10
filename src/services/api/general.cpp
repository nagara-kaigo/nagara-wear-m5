#include "general.h"
#include "api.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>

extern WiFiClientSecure client;
extern WebSocketsClient webSocket;

String message = R"rawliteral(
  {
    "type": "start",
    "input": {
      "text": "Hello from ESP32!"
    }
  }
  )rawliteral";
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected");
      webSocket.sendTXT(message);
      break;
    case WStype_TEXT:
      Serial.printf("Received: %s\n", payload);
      break;
    default:
      break;
  }
}




// HTTP POST リクエストの共通処理
String httpPostJson(MyApi& api, const String& endpoint, const String& jsonBody, const String& token) {
    //WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    String url = api.getBaseUrl() + endpoint;
    String payload;
  
    if (http.begin(client, url)) {
      http.setTimeout(20000); 
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
  String httpGet(MyApi& api, const String& endpoint, const String& token) {
    //WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    String url = api.getBaseUrl() + endpoint;
    String payload;
  
    if (http.begin(client, url)) {
      http.setTimeout(20000);
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
  String httpPatchJson(MyApi& api, const String& endpoint, const String& jsonBody, const String& token) {
    //WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    String payload;
    String url = api.getBaseUrl() + endpoint;
    if (!http.begin(client, url)) {
      http.setTimeout(20000);
        payload = "[HTTP] Unable to connect " + url;
    }
    http.setTimeout(20000);
  
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
  