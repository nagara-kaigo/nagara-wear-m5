#include "screen_pick_user.h"

void showUserPickerScreen() {
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("User Picker Screen");
    M5.Lcd.println("Press A for Receiver Picker");
}
