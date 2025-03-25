#include "API.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



//JSONパース関数(HTTPを考慮しない)
//JSONから任意のパーツを取り出す
String getJsonValue(const String& jsonText, const String& part) {
  // 1) JSON解析用のドキュメントを用意（バッファサイズ 1024）
  DynamicJsonDocument doc(1024);

  // 2) JSON文字列をdocにパース
  DeserializationError error = deserializeJson(doc, jsonText);
  if (error) {
    // パース失敗時はログを出して空文字を返す
    Serial.println("[Error] Failed to parse JSON");
    return "";
  }

  // 3) doc[part] から値を取得
  //    ここで .as<String>() を使って Arduino String に変換
  if (doc[part].isNull()) {
    // 指定したキーがJSONに含まれていない場合も空文字を返す
    return "";
  }

  // キーが存在すれば文字列として取得
  String value = doc[part].as<String>();
  return value;
}


String getValueInJson(const String& jsonText, const String& part, const String& field) {
  // 1) JSONをパースする
  DynamicJsonDocument doc(2048); // 必要に応じて容量調整
  DeserializationError error = deserializeJson(doc, jsonText);
  if (error) {
    Serial.print("[Error] Failed to parse JSON: ");
    Serial.println(error.c_str());
    return "";
  }

  // 2) "items" が配列か確認
  if (!doc[part].is<JsonArray>()) {
    Serial.println("[Error] 'items' is not an array or not found");
    return "";
  }
  JsonArray itemsArray = doc[part].as<JsonArray>();
  if (itemsArray.size() == 0) {
    Serial.println("[Error] 'items' array is empty");
    return "";
  }

  // 3) 配列の先頭要素(0番目)から、指定したキーの値を取得
  //    もしキーが存在しなければ空文字を返す
  String result = itemsArray[0][field] | "";

  return result;
}



// コンストラクタ: APIのベースURLを設定
MyApi::MyApi(const String& baseUrl) : _baseUrl(baseUrl) {}

// ログイン
String MyApi::loginToApi(const String& ID, const String& password) {
  String jsonBody = "{ \"loginId\": \"" + ID + "\", \"password\": \"" + password + "\" }";
  return httpPostJson("/auth/login", jsonBody);
}

// テナント一覧ゲット
String MyApi::get_Tenants(const String& token) {
  return httpGet("/tenants", token);
}

//ログインユーザー情報ゲット
String MyApi::get_Me(const String& token) {
    return httpGet("/auth/me", token);
  }

//チャット一覧ゲット
String MyApi::get_Chats(const String& token){
    return httpGet("/chats", token);
}

//テナントユーザ一覧を取得
String MyApi::get_tenantResident(const String& token){
  return httpGet("/tenants/" + tenantUid + "/residents", token);
}

//レジデント作成
// MyApi.cpp

String MyApi::CreateResidents(const String& token,
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


//食事記録作成
String MyApi::CreateFoodRecord(const String& token,
  const String& residentUid,
  const String& recordedAt,
  const String& notes,
  const String& mealTime,
  int mainCoursePercentage,
  int sideDishPercentage,
  int soupPercentage,
  const String& beverageType,
  int beverageVolume)
{
// 1) JSONボディを組み立てる
String jsonBody = "{";
jsonBody += "\"recordedAt\":\""           + recordedAt           + "\",";
jsonBody += "\"notes\":\""                + notes                + "\",";
jsonBody += "\"mealTime\":\""             + mealTime             + "\",";
jsonBody += "\"mainCoursePercentage\":"   + String(mainCoursePercentage) + ",";
jsonBody += "\"sideDishPercentage\":"     + String(sideDishPercentage)   + ",";
jsonBody += "\"soupPercentage\":"         + String(soupPercentage)       + ",";
jsonBody += "\"beverageType\":\""         + beverageType         + "\",";
jsonBody += "\"beverageVolume\":"         + String(beverageVolume);
jsonBody += "}";

// 2) APIエンドポイントを組み立て
String endpoint = "/residents/" + residentUid + "/food-records";

// 3) POSTリクエストを送信 (httpPostJsonを利用)
return httpPostJson(endpoint, jsonBody, token);
}

String MyApi::foodTranscription(const String& transcription){
  String jsonBody = "{";
  jsonBody += "\"transcription\":\"" + transcription;
  jsonBody += "}";

  String endpoint = "/residents/" + residentUid + "/food-records";

  return httpPostJson(endpoint, jsonBody, userToken);
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
