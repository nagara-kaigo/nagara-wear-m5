#include "time_manager.h"
#include <time.h>

void initializeTime() {
    configTime(9 * 3600, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); // JST = UTC+9
    while (time(nullptr) < 100000) {  // NTPの応答待ち
        delay(100);
        Serial.print(".");
    }
    Serial.println("\nTime initialized");
}

String getFormattedTime() {
    time_t now = time(nullptr);
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);  // UTC時間で取得
    char buf[25];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);  // ISO 8601
    return String(buf);
}