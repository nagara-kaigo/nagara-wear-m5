#ifndef DAILY_RECORDS_H
#define DAILY_RECORDS_H

#include <Arduino.h>
class MyApi; // 前方宣言

// 日常記録からの情報抽出
String dailyRecordInfo(MyApi& api);


// 日常記録作成
String createDailyRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& dailyMethod
);


// 日常記録追記
String dailyTranscription(MyApi& api, const String& transcription);

#endif
