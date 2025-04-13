#include "template_bath_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      

void showDailyRecordFromJson(const JsonDocument& doc) {
    const char* dailyStatus = doc["dailyStatus"] | "Unknown";
    const char* notes = doc["notes"] | "";
 
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(0, 60);

    M5.Lcd.print("状態: ");
    M5.Lcd.println(dailyStatus);
 
    M5.Lcd.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Lcd.println(notes);
    } else {
        M5.Lcd.println("なし");
    }
}
