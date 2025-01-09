#ifndef SCREEN_STANDBY_H
#define SCREEN_STANDBY_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

void showStandbyScreen(const AppState &state);
bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state);

#endif
