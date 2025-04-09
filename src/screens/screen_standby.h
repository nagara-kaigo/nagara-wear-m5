#ifndef SCREEN_STANDBY_H
#define SCREEN_STANDBY_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

#define MEALTIME_RECTWIDTH 80     // 幅
#define MEALTIME_RECTHEIGHT 80     // 高さ
#define GAP 10     // 四角同士の間隔
#define MEALTIME_STARTX 40     // 一番左の四角の描画開始X座標
#define MEALTIME_STARTY 80     // 四角の描画開始Y座標
#define RECORD_RECTWIDTH  120
#define RECORD_RECTHEIGHT  80
#define RECORD_STARTX  100
#define RECORD_STARTY  80

void showStandbyScreen(const AppState &state);
bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state);

#endif
