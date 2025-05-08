#include "screen_pick_record_type.h"
#include "main.h" // AppState を参照
#include "../ui/header.h"
#include "../ui/footer.h"

void showRecordTypeScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK, TFT_WHITE);
    String title = "利用者:" + state.selectedResident.familyName + " " + state.selectedResident.givenName;
    showHeaderBar(title);
    M5.Display.drawRect(69,  40, 86, 75, TFT_BLACK);   // 上段 左
    M5.Display.drawRect(165, 40, 86, 75, TFT_BLACK);  // 上段 右
    M5.Display.drawRect(21,  125, 86, 75, TFT_BLACK); // 下段 左
    M5.Display.drawRect(117, 125, 86, 75, TFT_BLACK); // 下段 中
    M5.Display.drawRect(213, 125, 86, 75, TFT_BLACK); // 下段 右
    M5.Display.setTextDatum(textdatum_t::middle_center); // Middle-Center
    M5.Display.drawString("食事", 112, 77);
    M5.Display.drawString("飲料", 208, 77);
    M5.Display.drawString("排泄", 64, 162);
    M5.Display.drawString("入浴", 160, 162);
    M5.Display.drawString("日常", 256, 162);

    showFooterBar(state);
}


bool handleRecordTypeTouch(const lgfx::v1::touch_point_t& touch, AppState &state) {
    if (touch.x > 69 && touch.x < 69+86 && touch.y > 40 && touch.y < 40+75) {
        state.selectedRecordType = MEAL;
        return true;
    } else if (touch.x > 165 && touch.x < 165+86 && touch.y > 40 && touch.y < 40+75) {
        state.selectedRecordType = DRINK;
        return true;
    }else if (touch.x > 21 && touch.x < 21+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = EXCRETION;
        return true;
    }else if (touch.x > 117 && touch.x < 117+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = BATH;
        return true;
    }else if (touch.x > 213 && touch.x < 213+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = EVERYDAY;
        return true;
    }
    return false;
}