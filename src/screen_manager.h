#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "main.h"
#include "config.h"
#include "screens/screen_pick_user.h"
#include "screens/screen_pick_resident.h"
#include "screens/screen_standby.h"
#include "screens/screen_transcription.h"
#include "screens/extracts/screen_food_extract.h"
#include "screens/screen_pick_record_type.h"

void changeScreen(Screen newScreen, bool addStuck = true);
void popScreen();
    

#endif // SCREEN_MANAGER_H