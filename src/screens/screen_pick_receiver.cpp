#include "screen_pick_receiver.h"

void showReceiverPickerScreen(const AppState &state) {
    M5.Lcd.clear();
    showFooterBar(state);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("User: " + state.selectedUser);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.print("Select Receiver:");
    M5.Lcd.fillRect(10, 70, 300, 50, BLUE); // ボタン
    M5.Lcd.setCursor(60, 160);
    M5.Lcd.print("Receiver1");
}

bool handleReceiverPickerTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 10 && touch.x < 310 && touch.y > 70 && touch.y < 120) { // ボタン領域
        state.selectedReceiver = String(CARE_RECEIVER_UUID_1);
        return true;
    }
    return false;
}
