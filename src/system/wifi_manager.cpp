#include "wifi_manager.h"
#include <WiFi.h>
#include "config.h"
#include <M5Core2.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void connectToWiFi() {
    WiFi.begin(ssid, password);
    M5.Lcd.fillRect(0, 140, 340, 120, WHITE);
    M5.Lcd.drawString("ネットワーク通信中", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    M5.Lcd.fillRect(0, 140, 340, 120, WHITE);
    Serial.println("WiFi Connected!");
    M5.Lcd.drawString("ネットワーク通信成功", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
}