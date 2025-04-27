#ifndef SCREEN_PICK_RECORD_TYPE_H
#define SCREEN_PICK_RECORD_TYPE_H

#include <M5Unified.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

void showRecordTypeScreen(const AppState &state);
bool handleRecordTypeTouch(const lgfx::v1::touch_point_t& touch, AppState &state);

#endif
