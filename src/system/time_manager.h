#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>

void initializeTime();
String getFormattedTime();  // 必要に応じて整形した時刻文字列を取得

#endif