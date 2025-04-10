#ifndef DAILY_RECORDS_H
#define DAILY_RECORDS_H

#include <Arduino.h>
#include "../api.h"

//食事記録からの情報抽出
String dailyRecordInfo(MyApi& api);


//食事記録作成
String createDailyRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& dailyStatus
);


//食事記録追記
String dailyTranscription(MyApi& api, const String& transcription);

#endif
