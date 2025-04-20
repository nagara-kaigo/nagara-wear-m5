#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "main.h"

void changeScreen(Screen newScreen, bool addStuck = true);
void popScreen();
void wifiDisconnectionPopup();
    

#endif // SCREEN_MANAGER_H