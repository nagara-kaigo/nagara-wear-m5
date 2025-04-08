#include "bath_records.h"
#include <ArduinoJson.h>
#include "api.h"
#include "general.h"

//食事記録作成
String createBathRecord(
    MyApi& api,
    const String& token,
    const String& residentUid,
    const String& recordedAt,
    const String& notes,
    const String& bathMethod
) {
  // 1) JSONボディを組み立てる
  String jsonBody = "{";
  jsonBody += "\"recordedAt\":\""           + recordedAt           + "\",";
  jsonBody += "\"notes\":\""                + notes                + "\",";
  jsonBody += "\"bathMethod\":\""           + bathMethod                  ;
  jsonBody += "}";
  
  // 2) APIエンドポイントを組み立て
  String endpoint = "/residents/" + residentUid + "/bath-records";
  
  // 3) POSTリクエストを送信 (httpPostJsonを利用)
  return httpPostJson(api, endpoint, jsonBody, token);
  }
  
  // 入浴記録の追記
  String bathTranscription(MyApi& api, const String& transcription){
    String jsonBody = "{";
    jsonBody += "\"transcription\":\"" + transcription + "\"";
    jsonBody += "}";
  
    String endpoint = "/residents/" + api.getResidentUid() + "/bath-records/" + api.getRecordUid() + "/transcription";
    return httpPatchJson(api,endpoint, jsonBody, api.getuserToken());
  }
  
  
  // 入浴記録からの情報抽出
  String bathRecordInfo(MyApi& api){
    String jsonBody = "{}";
    String endpoint = "/residents/" + api.getResidentUid() + "/bath-records/" + api.getRecordUid() + "/extract";
    return httpPostJson(api, endpoint, jsonBody, api.getuserToken());
  }