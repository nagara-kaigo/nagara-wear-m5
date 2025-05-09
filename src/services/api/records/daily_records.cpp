#include "daily_records.h"
#include <ArduinoJson.h>
#include "../general.h"
#include "../api.h"

// 日常記録作成
String createDailyRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& dailyStatus
) {
  JsonDocument doc;
  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["dailyStatus"] = dailyStatus;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records";
  return httpPostJson(api, endpoint, jsonBody, api.getUserToken());
}
  
// 日常記録の追記
String dailyTranscription(MyApi& api, const String& transcription){
  JsonDocument doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getUserToken());
}
  
// 日常記録からの情報抽出
String dailyRecordInfo(MyApi& api){
  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records/" + api.getRecordUid() + "/extract";
  return httpGet(api, endpoint, api.getUserToken());
}