#ifndef SCREEN_PICK_RECORD_TYPE_H
#define SCREEN_PICK_RECORD_TYPE_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

void showRecordTypeScreen(const AppState &state);
bool handleRecordTypeTouch(const TouchPoint_t &touch, AppState &state);

#endif
