#ifndef SCREEN_DISPLAY_EXTRACT_H
#define SCREEN_DISPLAY_EXTRACT_H

#include <Arduino.h>

struct AppState; // 前方宣言

void showRecordFromJson(const String &jsonString, const AppState &state);

#endif // SCREEN_DISPLAY_EXTRACT_H
