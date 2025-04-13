#ifndef SCREEN_PICK_RECORD_TYPE_H
#define SCREEN_PICK_RECORD_TYPE_H

#include <M5Core2.h>
struct AppState; // 前方宣言

void showRecordTypeScreen(const AppState &state);
bool handleRecordTypeTouch(const TouchPoint_t &touch, AppState &state);

#endif
