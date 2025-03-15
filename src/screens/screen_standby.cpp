#include "screen_standby.h"

/*
ButtonColors onCol = {RED, WHITE, WHITE};
ButtonColors offCol = {BLACK, WHITE, WHITE};
Button myButton(160, 120, 240, 100, false, "REC", offCol, onCol, TC_DATUM, 0, 0, 10);
*/

void showStandbyScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    showHeaderBar("RECボタンで開始します");
    M5.Lcd.setCursor(10,40);
    M5.Lcd.setTextDatum(0);
    //M5.Lcd.drawString("User: " + state.selectedUser, 10, 40);
    M5.Lcd.drawString("利用者: 介護士A", 10, 40);
    //myButton.draw();
    M5.Lcd.drawRect(100, 80, 120, 80, BLACK);
    M5.Lcd.setTextDatum(4);
    M5.Lcd.drawString("REC", 160, 120);

    showFooterBar(state);
}

bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 100 && touch.x < 220 && touch.y > 80 && touch.y < 160) {
        return true;
    }
    return false;
}