#include "elimination_records.h"
#include <ArduinoJson.h>
#include "../general.h"

// 排泄記録作成
String createEliminationRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& eliminationMethod,
  boolean hasFeces,
  boolean fecalIncontinence,
  const String& fecesAppearance,
  int fecesVolume,
  boolean hasUrine,
  boolean urineIncontinence,
  const String& urineAppearance,
  int urineVolume
) {
  StaticJsonDocument<256> doc;
  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["eliminationMethod"] = eliminationMethod;
  doc["hasFeces"] = hasFeces;
  doc["fecalIncontinence"] = fecalIncontinence;
  doc["fecesAppearance"] = fecesAppearance;
  doc["fecesVolume"] = fecesVolume;
  doc["hasUrine"] = hasUrine;
  doc["urineIncontinence"] = urineIncontinence;
  doc["urineAppearance"] = urineAppearance;
  doc["urineVolume"] = urineVolume;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/elimination-records";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 排泄記録の追記
String eliminationTranscription(MyApi& api, const String& transcription){
  StaticJsonDocument<128> doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/elimination-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 排泄記録からの情報抽出
String eliminationRecordInfo(MyApi& api){
  String jsonBody = "{}";
  String endpoint = "/residents/" + api.getResidentUid() + "/elimination-records/" + api.getRecordUid() + "/extract";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}