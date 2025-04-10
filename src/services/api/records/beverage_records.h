#ifndef BEVERAGE_RECORDS_H
#define BEVERAGE_RECORDS_H

#include <Arduino.h>
#include "../api.h"

//食事記録からの情報抽出
String beverageRecordInfo(MyApi& api);


//食事記録作成
String createBeverageRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& beverageType,
  int volume
);


//食事記録追記
String beverageTranscription(MyApi& api, const String& transcription);

#endif
