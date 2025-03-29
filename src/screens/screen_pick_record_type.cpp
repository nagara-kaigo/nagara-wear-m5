#include "screen_pick_record_type.h"

void showRecordTypeScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    showHeaderBar("記録の種類を選んでください");
    M5.Lcd.drawRect(69,  40, 86, 75, BLACK);   // 上段 左
    M5.Lcd.drawRect(165, 40, 86, 75, BLACK);  // 上段 右
    M5.Lcd.drawRect(21,  125, 86, 75, BLACK); // 下段 左
    M5.Lcd.drawRect(117, 125, 86, 75, BLACK); // 下段 中
    M5.Lcd.drawRect(213, 125, 86, 75, BLACK); // 下段 右
    M5.Lcd.setTextDatum(MC_DATUM); // Middle-Center
    M5.Lcd.drawString("食事", 112, 77);
    M5.Lcd.drawString("飲料", 208, 77);
    M5.Lcd.drawString("排泄", 64, 162);
    M5.Lcd.drawString("入浴", 160, 162);
    M5.Lcd.drawString("日常", 256, 162);

    showFooterBar(state);
}


bool handleRecordTypeTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 69 && touch.x < 69+86 && touch.y > 40 && touch.y < 75) {
        state.selectRecordType = String("MEAL");
        return true;
    } else if (touch.x > 165 && touch.x < 280 && touch.y > 110 && touch.y < 170) {
        state.selectedUser = String("hogehoge");
        return true;
    }
    return false;
}