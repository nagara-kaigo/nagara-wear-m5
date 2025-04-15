#include "wifi_manager.h"
#include <WiFi.h>
#include "config.h"
#include <M5Core2.h>

//const char* ssid = WIFI_SSID;
//const char* password = WIFI_PASSWORD;

void connectToWiFi(String ssid, String password) {
    M5.Lcd.fillRect(0, 140, 340, 120, WHITE);
    M5.Lcd.drawString("ネットワーク通信中...", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    M5.Lcd.fillRect(0, 140, 340, 120, WHITE);
    Serial.println("WiFi Connected!");
    M5.Lcd.drawString("ネットワーク通信成功", M5.Lcd.width() / 2, M5.Lcd.height() * 3 / 4);
}

bool wifiDisconnectionObserve(){
    switch (WiFi.status())
    {
    case WL_NO_SHIELD:
        return false;
    
    case WL_CONNECTED:
        return true;

    case WL_NO_SSID_AVAIL:
        return false;
    
    case WL_CONNECT_FAILED:
        return false;
    
    case WL_CONNECTION_LOST:
        return false;
    
    case WL_DISCONNECTED:
        return false;
    default:
        return false;
    }
}