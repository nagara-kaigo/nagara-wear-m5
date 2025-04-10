#include "beverage_records.h"
#include <ArduinoJson.h>
#include "../general.h"

// 飲料記録作成
String createBeverageRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& beverageType,
  int volume
) {
  StaticJsonDocument<256> doc;
  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["beverageType"] = beverageType;
  doc["volume"] = volume;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/beverage-records";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 飲料記録の追記
String beverageTranscription(MyApi& api, const String& transcription){
  StaticJsonDocument<128> doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/beverage-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 飲料記録からの情報抽出
String beverageRecordInfo(MyApi& api){
  String jsonBody = "{}";
  String endpoint = "/residents/" + api.getResidentUid() + "/beverage-records/" + api.getRecordUid() + "/extract";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}