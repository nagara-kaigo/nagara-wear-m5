#include "footer.h"
#include <M5Core2.h>

void showFooterBar(const AppState &state) {
    M5.Lcd.fillRect(0, 200, 320, 40, WHITE);
    M5.Lcd.drawLine(10, 210, 310, 210, BLACK);
    M5.Lcd.setTextDatum(5);
    M5.Lcd.drawString("戻る", 80, 225);
    M5.Lcd.setTextDatum(4);
    M5.Lcd.drawString("ホーム", 160, 225);
    M5.Lcd.setTextDatum(3);
    M5.Lcd.drawString("メニュー", 240, 225);
}


void showFooterBarRecording(const AppState &state) {
    M5.Lcd.fillRect(0, 200, 320, 40, WHITE);
    M5.Lcd.drawLine(10, 210, 310, 210, BLACK);
    M5.Lcd.setTextDatum(5);
    M5.Lcd.drawString("停止", 80, 225);
    M5.Lcd.setTextDatum(4);
    M5.Lcd.drawString("ホーム", 160, 225);
    M5.Lcd.setTextDatum(3);
    M5.Lcd.drawString("メニュー", 240, 225);
}