#include "network.h"
#include <WiFi.h>
#include "config.h"

void initNetwork() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}

void sendData(const char* data) {
    Serial.printf("Sending data: %s\n", data);
}
