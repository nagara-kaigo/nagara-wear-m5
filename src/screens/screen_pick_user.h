#ifndef SCREEN_PICK_USER_H
#define SCREEN_PICK_USER_H

#include <M5Unified.h>
struct AppState; // 前方宣言

void showUserPickerScreen(const AppState &state);
bool handleUserPickerTouch(const lgfx::v1::touch_point_t& touch, AppState &state);


#endif
