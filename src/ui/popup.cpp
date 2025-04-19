#include "popup.h"
#include <M5Core2.h>
void showWifiDisconnectedPopup(const AppState &state){
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.fillRect(WIFI_POPUP_STARTX, WIFI_POPUP_STARTY, WIFI_POPUP_WIDTH, WIFI_POPUP_HEIGHT, WHITE);
    M5.Lcd.drawRect(WIFI_POPUP_STARTX, WIFI_POPUP_STARTY, WIFI_POPUP_WIDTH, WIFI_POPUP_HEIGHT, BLACK);
    M5.Lcd.drawString("ネットワークがありません",WIFI_POPUP_STARTX + WIFI_POPUP_WIDTH/2, WIFI_POPUP_STARTY + WIFI_POPUP_HEIGHT/2);
}