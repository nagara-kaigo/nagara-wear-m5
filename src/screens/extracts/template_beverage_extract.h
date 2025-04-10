#ifndef TEMPLATE_BEVERAGE_EXTRACT_H
#define TEMPLATE_BEVERAGE_EXTRACT_H

#include <Arduino.h>
#include "screen_manager.h"
#include <ArduinoJson.h>  

void showBeverageRecordFromJson(const JsonDocument& doc);

#endif // SCREEN_DISPLAY_EXTRACT_H
