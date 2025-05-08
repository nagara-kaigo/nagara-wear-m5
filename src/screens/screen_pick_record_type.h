#ifndef SCREEN_PICK_RECORD_TYPE_H
#define SCREEN_PICK_RECORD_TYPE_H

#include <M5Unified.h>
struct AppState; // 前方宣言

void showRecordTypeScreen(const AppState &state);
bool handleRecordTypeTouch(const lgfx::v1::touch_point_t& touch, AppState &state);

#endif
