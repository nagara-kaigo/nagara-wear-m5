#include "template_beverage_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      

void showBeverageRecordFromJson(const JsonDocument& doc) {
    const char* beverageType = doc["beverageType"] | "Unknown";
    int volume = doc["volume"] | -1;
    const char* notes = doc["notes"] | "";
 
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(0, 60);

    M5.Lcd.print("種類: ");
    M5.Lcd.println(beverageType);
 
    M5.Lcd.print("飲んだ量: ");
    if (volume >= 0) {
        M5.Lcd.printf("%d ml\n", volume);
    } else {
        M5.Lcd.println("不明");
    }

    // 特記事項
    M5.Lcd.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Lcd.println(notes);
    } else {
        M5.Lcd.println("なし");
    }
}