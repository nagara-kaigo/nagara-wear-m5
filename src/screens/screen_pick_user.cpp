#include "screen_pick_user.h"
#include "main.h" // AppState を参照
#include "../ui/header.h"
#include "../ui/footer.h"

void showUserPickerScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK, TFT_WHITE);
    showHeaderBar("利用者を選んでください");
    M5.Display.drawRect(20, 40, 260, 60, TFT_BLACK);
    M5.Display.drawRect(20, 110, 260, 60, TFT_BLACK);
    M5.Display.drawRect(20, 180, 260, 60, TFT_BLACK);
    M5.Display.setTextDatum(textdatum_t::middle_left);
    M5.Display.drawString("こた", 30, 70);
    M5.Display.drawString("ゆうせい", 30, 140);

    showFooterBar(state);
}

bool handleUserPickerTouch(const lgfx::v1::touch_point_t& touch, AppState &state) {
    if (touch.x > 20 && touch.x < 280 && touch.y > 40 && touch.y < 100) {
        state.userName = "こた";
        return true;
    } else if (touch.x > 20 && touch.x < 280 && touch.y > 110 && touch.y < 170) {
        state.userName = "ゆうせい";
        return true;
    }
    return false;
}