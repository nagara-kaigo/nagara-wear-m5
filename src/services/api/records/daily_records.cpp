#include "daily_records.h"
#include <ArduinoJson.h>
#include "../general.h"

//入浴記録作成
String createDailyRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& dailyStatus
) {
  StaticJsonDocument<256> doc;
  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["dailyStatus"] = dailyStatus;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 入浴記録の追記
String dailyTranscription(MyApi& api, const String& transcription){
  StaticJsonDocument<128> doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 入浴記録からの情報抽出
String dailyRecordInfo(MyApi& api){
  String jsonBody = "{}";
  String endpoint = "/residents/" + api.getResidentUid() + "/daily-records/" + api.getRecordUid() + "/extract";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}