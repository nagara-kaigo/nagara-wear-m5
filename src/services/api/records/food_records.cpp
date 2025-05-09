#include "food_records.h"
#include <ArduinoJson.h>
#include "../api.h"
#include "../general.h"

// 食事記録作成
String createFoodRecord(
    MyApi& api,
    const String& recordedAt,
    const String& notes,
    const String& mealTime,
    int mainCoursePercentage,
    int sideDishPercentage,
    int soupPercentage,
    const String& beverageType,
    int beverageVolume)
{
  JsonDocument doc;

  doc["recordedAt"] = recordedAt;
  doc["notes"] = notes;
  doc["mealTime"] = mealTime;
  doc["mainCoursePercentage"] = mainCoursePercentage;
  doc["sideDishPercentage"] = sideDishPercentage;
  doc["soupPercentage"] = soupPercentage;
  doc["beverageType"] = beverageType;
  doc["beverageVolume"] = beverageVolume;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/food-records";
  return httpPostJson(api, endpoint, jsonBody, api.getUserToken());
}

// 食事記録の追記
String foodTranscription(MyApi& api, const String& transcription){
  JsonDocument doc;
  doc["transcription"] = transcription;

  String jsonBody;
  serializeJson(doc, jsonBody);

  String endpoint = "/residents/" + api.getResidentUid() + "/food-records/" + api.getRecordUid() + "/transcription";
  return httpPatchJson(api, endpoint, jsonBody, api.getUserToken());
}

// 食事記録からの情報抽出
String foodRecordInfo(MyApi& api){
  String jsonBody = "{}";
  String endpoint = "/residents/" + api.getResidentUid() + "/food-records/" + api.getRecordUid() + "/extract";
  return httpPostJson(api, endpoint, jsonBody, api.getUserToken());
}