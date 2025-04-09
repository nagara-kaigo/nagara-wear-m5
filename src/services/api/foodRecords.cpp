#include "foodRecords.h"
#include <ArduinoJson.h>
#include "api.h"
#include "general.h"

//食事記録作成
String createFoodRecord(
    MyApi& api,
    const String& token,
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
  return httpPostJson(api, endpoint, jsonBody, token);
  }
  
  //食事記録の追記
  String foodTranscription(MyApi& api, const String& transcription){
    String jsonBody = "{";
    jsonBody += "\"transcription\":\"" + transcription + "\"";
    jsonBody += "}";
  
    String endpoint = "/residents/" + api.getResidentUid() + "/food-records/" + api.getRecordUid() + "/transcription";
    return httpPatchJson(api,endpoint, jsonBody, api.getuserToken());
  }
  
  
  
  //食事記録からの情報抽出
  String foodRecordInfo(MyApi& api){
    String jsonBody = "{}";
    String endpoint = "/residents/" + api.getResidentUid() + "/food-records/" + api.getRecordUid() + "/extract";
    return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
  }