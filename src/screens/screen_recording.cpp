#include "screen_recording.h"

void showRecordingScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.setTextColor(RED, BLACK);
    showHeaderBar("AI文字起こし中!");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(0,60);
    M5.Lcd.print("氏名: \n食事の種類: \n主食: \n副菜: \n汁物: \n特記事項");
    showFooterBar(state);

    delay(15000);

    M5.Lcd.clear();
    M5.Lcd.setTextColor(RED, BLACK);
    showHeaderBar("AI文字起こし中!");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(0,60);
    M5.Lcd.print("氏名: 春日井太郎さん");
    M5.Lcd.print("\n食事の種類: 昼食");
    M5.Lcd.print("\n主食: 1/10");
	M5.Lcd.print("\n副菜: 2/10");
    //M5.Lcd.setTextColor(GREEN, BLACK);
	//M5.Lcd.print(" 完了");
    //M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.print("\n汁物: 0/10");
	M5.Lcd.print("\n特記事項: 途中で手が止まってしまった。水分はほとんど摂ってない。");
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