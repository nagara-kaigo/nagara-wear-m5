#include "screen_recording.h"

void showRecordingScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(RED, WHITE);
    showHeaderBar("AI文字起こし中!");
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(0,60);
    M5.Lcd.print("氏名: \n食事の種類: \n主食: \n副菜: \n汁物: \n水分: \n特記事項");
    showFooterBar(state);

    delay(10000);

    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(RED, WHITE);
    showHeaderBar("AI文字起こし中!");
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(0,60);
    M5.Lcd.print("氏名: ながらさん");
    M5.Lcd.print("\n食事の種類: 昼食");
    M5.Lcd.print("\n主食: |==========|");
    M5.Lcd.setTextColor(GREEN, WHITE);
	M5.Lcd.print(" (100%)");
    M5.Lcd.setTextColor(BLACK, WHITE);
	M5.Lcd.print("\n副菜: |==========|");
    M5.Lcd.setTextColor(GREEN, WHITE);
    M5.Lcd.print(" (100%)");
    M5.Lcd.setTextColor(BLACK, WHITE);
	M5.Lcd.print("\n汁物:");
	M5.Lcd.print("\n水分:");
	M5.Lcd.print("\n特記事項: ");
    showFooterBar(state);
 
    delay(5000);

    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(RED, WHITE);
    showHeaderBar("AI文字起こし中!");
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(0,60);
    M5.Lcd.print("氏名: ながらさん");
    M5.Lcd.print("\n食事の種類: 昼食");
    M5.Lcd.print("\n主食: |==========|");
    M5.Lcd.setTextColor(GREEN, WHITE);
	M5.Lcd.print(" (100%)");
    M5.Lcd.setTextColor(BLACK, WHITE);
	M5.Lcd.print("\n副菜: |==========|");
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.print(" (100%)");
    M5.Lcd.setTextColor(BLACK, WHITE);
	M5.Lcd.print("\n汁物: |=====|");
    M5.Lcd.print(" (50%)");
	M5.Lcd.print("\n水分: 100ml");
	M5.Lcd.print("\n特記事項: 汁物をこぼしてしまわれました");
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