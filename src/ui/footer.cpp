#include "footer.h"

void showFooterBar(const AppState &state) {
    M5.Lcd.fillRect(0, 200, 320, 40, BLACK);
    M5.Lcd.drawLine(10, 210, 310, 210, WHITE);
    M5.Lcd.setTextDatum(5);
    M5.Lcd.drawString("back", 80, 225);
    M5.Lcd.setTextDatum(4);
    M5.Lcd.drawString("Home", 160, 225);
    M5.Lcd.setTextDatum(3);
    M5.Lcd.drawString("setting", 240, 225);
}