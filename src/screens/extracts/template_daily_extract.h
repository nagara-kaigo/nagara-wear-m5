#ifndef TEMPLATE_DAILY_EXTRACT_H
#define TEMPLATE_DAILY_EXTRACT_H

#include <Arduino.h>
#include "screen_manager.h"
#include <ArduinoJson.h>  

void showDailyRecordFromJson(const JsonDocument& doc);

#endif // SCREEN_DISPLAY_EXTRACT_H
