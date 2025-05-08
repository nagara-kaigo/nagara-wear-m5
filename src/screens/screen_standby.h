#ifndef SCREEN_STANDBY_H
#define SCREEN_STANDBY_H

#include <Arduino.h>
#include <M5Unified.h>

struct AppState; // 前方宣言

#define MEALTIME_RECTWIDTH 80     // 幅
#define MEALTIME_RECTHEIGHT 80     // 高さ
#define GAP 10     // 四角同士の間隔
#define MEALTIME_STARTX 40     // 一番左の四角の描画開始X座標
#define MEALTIME_STARTY 80     // 四角の描画開始Y座標
#define CENTER_RECTWIDTH  120
#define CENTER_RECTHEIGHT  80
#define CENTER_STARTX  100
#define CENTER_STARTY  80

void showStandbyScreen(const AppState &state);
bool handleRecBtnTouch(const lgfx::v1::touch_point_t& touch, AppState &state);

#endif
