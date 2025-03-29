#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "main.h"
#include "config.h"
#include "screens/screen_pick_user.h"
#include "screens/screen_pick_receiver.h"
#include "screens/screen_standby.h"
#include "screens/screen_recording.h"
#include "screens/screen_transcription.h"


void changeScreen(Screen newScreen, bool addStuck = true);
void popScreen();
    

#endif // SCREEN_MANAGER_H