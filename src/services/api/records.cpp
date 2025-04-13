#include "records/food_records.h"
#include "records/bath_records.h"
#include "records/elimination_records.h"
#include "records/beverage_records.h"
#include "records/daily_records.h"
#include <ArduinoJson.h>
#include "main.h"
#include "api.h"
#include "general.h"

/*
//食事記録作成
String createRecord(
    MyApi& api,
    const String& token,
    const String& residentUid,
    const String& recordedAt)
  {
  // TODO: 食事記録の詳細情報を引数として受け取るようにする
  }
*/


//食事記録の追記
String patchRecordTranscription(
  MyApi& api,
  RecordType recordType,
  const String& transcription){
  switch (recordType) {
    case MEAL:
      return foodTranscription(api,transcription);
      break;
    case BATH:
      return bathTranscription(api,transcription);
      break;
    case EXCRETION:
      return eliminationTranscription(api,transcription);
      break;
    case DRINK:
      return beverageTranscription(api,transcription);
      break;
    case EVERYDAY:
      return dailyTranscription(api,transcription);
      break;
    default:
      return "error";
      break;
  }
}


//食事記録からの情報抽出
String fetchRecordInfo(MyApi& api, RecordType recordType){
  switch (recordType) {
  case MEAL:
    return foodRecordInfo(api);
    break;
  case BATH:
    return bathRecordInfo(api);
    break;
  case EXCRETION:
    return eliminationRecordInfo(api);
    break;
  case DRINK:
    return beverageRecordInfo(api);
    break;
  case EVERYDAY:
    return dailyRecordInfo(api);
    break;
  default:
    return "error";
    break;
  }
}
