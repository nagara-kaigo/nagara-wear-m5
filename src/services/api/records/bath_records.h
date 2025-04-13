#ifndef BATH_RECORDS_H
#define BATH_RECORDS_H

#include <Arduino.h>

class MyApi; // 前方宣言

//食事記録からの情報抽出
String bathRecordInfo(MyApi& api);


//食事記録作成
String createBathRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& bathMethod
);


//食事記録追記
String bathTranscription(MyApi& api, const String& transcription);

#endif
