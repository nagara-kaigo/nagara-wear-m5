#ifndef FOOD_RECORDS_H
#define FOOD_RECORDS_H

#include <Arduino.h>

class MyApi; // 前方宣言

/*
//食事記録作成
String createFoodRecord(
  MyApi& api,
  const String& token,
  const String& residentUid,
  const String& recordedAt);
*/

//食事記録追記
String patchRecordTranscription(
  MyApi& api, 
  RecordType recordType,
  const String& transcription);

//食事記録からの情報抽出
String fetchRecordInfo(MyApi& api, RecordType recordType);

#endif
