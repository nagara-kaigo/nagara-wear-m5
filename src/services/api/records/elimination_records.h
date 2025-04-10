#ifndef ELIMINATION_RECORDS_H
#define ELIMINATION_RECORDS_H

#include <Arduino.h>
#include "../api.h"

//食事記録からの情報抽出
String eliminationRecordInfo(MyApi& api);


//食事記録作成
String createEliminationRecord(
  MyApi& api,
  const String& recordedAt,
  const String& notes,
  const String& eliminationMethod,
  boolean hasFeces,
  boolean fecalIncontinence,
  const String& fecesAppearance,
  int fecesVolume,
  boolean hasUrine,
  boolean urineIncontinence,
  const String& urineAppearance,
  int urineVolume
);


//食事記録追記
String eliminationTranscription(MyApi& api, const String& transcription);

#endif
