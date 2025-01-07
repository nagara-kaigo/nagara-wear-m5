#include "screen_pick_receiver.h"

void showReceiverPickerScreen() {
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Receiver Picker Screen");
    M5.Lcd.println("Press A for User Picker");
}
