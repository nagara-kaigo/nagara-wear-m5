#ifndef SCREEN_PICK_RESIDENT_H
#define SCREEN_PICK_RESIDENT_H

#include <M5Core2.h>
#include <main.h>
struct AppState; // 前方宣言

#define ARROW_LEFT_X1 10
#define ARROW_LEFT_X2 30
#define ARROW_RIGHT_X1 310
#define ARROW_RIGHT_X2 290
#define ARROW_Y_CENTER 120
#define ARROW_Y_TOP 105
#define ARROW_Y_BOTTOM 135

#define BOX_LEFT_X 35
#define BOX_RIGHT_X 165
#define BOX_WIDTH 120
#define BOX_HEIGHT 50
#define BOX_START_Y 35
#define BOX_INTERVAL_Y 56

#define TEXT_OFFSET_X 10
#define TEXT_OFFSET_Y 20

void showResidentPickerScreen(AppState &state);
bool handleResidentPickerTouch(const TouchPoint_t &touch, AppState &state, SwipeState swipeState);

#endif
