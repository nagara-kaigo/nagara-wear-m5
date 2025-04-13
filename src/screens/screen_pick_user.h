#ifndef SCREEN_PICK_USER_H
#define SCREEN_PICK_USER_H

#include <M5Core2.h>
struct AppState; // 前方宣言

void showUserPickerScreen(const AppState &state);
bool handleUserPickerTouch(const TouchPoint_t &touch, AppState &state);

#endif
