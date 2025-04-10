#ifndef TEMPLATE_FOOD_EXTRACT_H
#define TEMPLATE_FOOD_EXTRACT_H

#include <Arduino.h>
#include "screen_manager.h"
#include <ArduinoJson.h>  

void showFoodRecordFromJson(const JsonDocument& doc);

#endif // SCREEN_DISPLAY_EXTRACT_H
