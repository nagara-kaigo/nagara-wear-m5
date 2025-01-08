#include "screen_pick_user.h"

void showUserPickerScreen(const AppState &state) {
    M5.Lcd.clear();
    showHeaderBar("pick user");
    M5.Lcd.drawRect(20, 40, 260, 60, WHITE);
    M5.Lcd.drawRect(20, 110, 260, 60, WHITE);
    M5.Lcd.drawRect(20, 180, 260, 60, WHITE);
    M5.Lcd.setTextDatum(3);
    M5.Lcd.drawString("test user", 30, 70);
    M5.Lcd.drawString("user1", 30, 140);

    showFooterBar(state);
}

bool handleUserPickerTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 20 && touch.x < 280 && touch.y > 40 && touch.y < 100) {
        state.selectedUser = String(DEFAULT_USER_UUID);
        return true;
    } else if (touch.x > 20 && touch.x < 280 && touch.y > 110 && touch.y < 170) {
        state.selectedUser = String("hogehoge");
        return true;
    }
    return false;
}