#include "screen_recording.h"

void showRecordingScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.setTextColor(RED, BLACK);
    showHeaderBar("Now Recording!");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(0,40);
    M5.Lcd.print("meal type: LUNCH");
    M5.Lcd.print("\nmainDish: 80%");
	M5.Lcd.print("\nsideDish: 100%");
    M5.Lcd.setTextColor(GREEN, BLACK);
	M5.Lcd.print(" OK");
    M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.print("\nsoup: 30%");
	M5.Lcd.print("\nnote: ");

    showFooterBar(state);
}

/*
bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 100 && touch.x < 220 && touch.y > 80 && touch.y < 160) {
        return true;
    }
    return false;
}
*/