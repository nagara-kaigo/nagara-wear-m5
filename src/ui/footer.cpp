#include "footer.h"

void showFooterBar(const AppState &state) {
    M5.Lcd.setCursor(80, 230);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRect(100, 220, 120, 20, BLUE);
    M5.Lcd.print("Home");
}