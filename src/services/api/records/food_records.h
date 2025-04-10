#ifndef FOOD_RECORDS_H
#define FOOD_RECORDS_H

#include <Arduino.h>
#include "../api.h"

//食事記録からの情報抽出
String foodRecordInfo(MyApi& api);


//食事記録作成
String createFoodRecord(
  MyApi& api,
  //const String& token,
  //const String& residentUid,
  const String& recordedAt,
  const String& notes,
  const String& mealTime,
  int mainCoursePercentage,
  int sideDishPercentage,
  int soupPercentage,
  const String& beverageType,
  int beverageVolume);


//食事記録追記
String foodTranscription(MyApi& api, const String& transcription);

#endif
