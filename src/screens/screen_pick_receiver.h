#ifndef SCREEN_PICK_RECEIVER_H
#define SCREEN_PICK_RECEIVER_H

#include <M5Core2.h>
#include "../../main.h" // AppState を参照
#include "../../config.h"

void showReceiverPickerScreen(const AppState &state);
bool handleReceiverPickerTouch(const TouchPoint_t &touch, AppState &state);

#endif
