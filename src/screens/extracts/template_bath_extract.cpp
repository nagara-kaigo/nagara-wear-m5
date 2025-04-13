#include "template_bath_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      

void showBathRecordFromJson(const JsonDocument& doc) {
    const char* bathMethod = doc["bathMethod"] | "Unknown";
    const char* notes = doc["notes"] | "";
 
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(0, 60);

    M5.Lcd.print("種類: ");
    M5.Lcd.println(bathMethod);
 
    M5.Lcd.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Lcd.println(notes);
    } else {
        M5.Lcd.println("なし");
    }
}
