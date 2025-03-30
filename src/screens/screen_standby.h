#ifndef SCREEN_STANDBY_H
#define SCREEN_STANDBY_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

#define RECTWIDTH 80     // 幅
#define RECTHEIGHT 80     // 高さ
#define GAP 10     // 四角同士の間隔
#define STARTX 40     // 一番左の四角の描画開始X座標
#define STARTY 80     // 四角の描画開始Y座標

void showStandbyScreen(const AppState &state);
bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state);

#endif
