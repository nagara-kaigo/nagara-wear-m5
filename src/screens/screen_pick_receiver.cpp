#include "screen_pick_receiver.h"

void showResidentPickerScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    showHeaderBar("利用者を選んでください");
    M5.Lcd.setTextDatum(3);
    size_t j=0;
    for(size_t i=0;i<state.selectedResidentGivenName.size();i++){
        M5.Lcd.drawRect(20, 35+(56*i), 120, 50, BLACK);
        M5.Lcd.drawRect(150, 35+(56*i), 120, 50, BLACK);
        if((i%2) == 0){
            M5.Lcd.drawString(state.selectedResidentGivenName[i], 30, 55+(56*j));
        }
        else{
            M5.Lcd.drawString(state.selectedResidentGivenName[i], 160, 55+(56*j));
            j=j+1;
        }
    }
    showFooterBar(state);
}

bool handleResidentPickerTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 20 && touch.x < 280 && touch.y > 40 && touch.y < 100) {
        state.selectedUser = "こた";
        return true;
    } else if (touch.x > 20 && touch.x < 280 && touch.y > 110 && touch.y < 170) {
        state.selectedUser = "ゆうせい";
        return true;
    }
    return false;
}
