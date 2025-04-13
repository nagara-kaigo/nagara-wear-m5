#ifndef SCREEN_DISPLAY_EXTRACT_H
#define SCREEN_DISPLAY_EXTRACT_H

struct AppState; // 前方宣言
#include <Arduino.h>

void showRecordFromJson(const String &jsonString, const AppState &state);

#endif // SCREEN_DISPLAY_EXTRACT_H
