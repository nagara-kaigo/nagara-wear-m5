#ifndef TEMPLATE_FOOD_EXTRACT_H
#define TEMPLATE_FOOD_EXTRACT_H

#include <ArduinoJson.h>  

#define BACKGROUND_COLOR WHITE
#define TEXT_COLOR       BLACK
#define TITLE_COLOR      RED

void showFoodRecordFromJson(const JsonDocument& doc);

#endif // SCREEN_DISPLAY_EXTRACT_H
