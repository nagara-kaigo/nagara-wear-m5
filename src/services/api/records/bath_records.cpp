#include "bath_records.h"
#include <ArduinoJson.h>
#include "../general.h"

//入浴記録作成
String createBathRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& bathMethod
) {
  StaticJsonDocument<256> doc;
  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["bathMethod"] = bathMethod;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/bath-records";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 入浴記録の追記
String bathTranscription(MyApi& api, const String& transcription){
  StaticJsonDocument<128> doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/bath-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getuserToken());
}
  
// 入浴記録からの情報抽出
String bathRecordInfo(MyApi& api){
  String jsonBody = "{}";
  String endpoint = "/residents/" + api.getResidentUid() + "/bath-records/" + api.getRecordUid() + "/extract";
  return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
}