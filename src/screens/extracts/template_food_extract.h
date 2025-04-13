#ifndef TEMPLATE_FOOD_EXTRACT_H
#define TEMPLATE_FOOD_EXTRACT_H

#define BACKGROUND_COLOR WHITE
#define TEXT_COLOR       BLACK
#define TITLE_COLOR      RED

#include <ArduinoJson.h>  

void showFoodRecordFromJson(const JsonDocument& doc);

#endif // SCREEN_DISPLAY_EXTRACT_H
