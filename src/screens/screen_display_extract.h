#ifndef SCREEN_DISPLAY_EXTRACT_H
#define SCREEN_DISPLAY_EXTRACT_H

#include <Arduino.h>

struct AppState; // 前方宣言

void showRecordFromJson(const AppState &state, const String &jsonString = "");

#endif // SCREEN_DISPLAY_EXTRACT_H
