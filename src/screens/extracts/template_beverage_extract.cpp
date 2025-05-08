#include "template_beverage_extract.h"
#include "screen_manager.h"
#include <M5Unified.h>      

void showBeverageRecordFromJson(const JsonDocument& doc) {
    const char* beverageType = doc["beverageType"] | "Unknown";
    int volume = doc["volume"] | -1;
    const char* notes = doc["notes"] | "";
 
    M5.Display.setTextColor(BLACK);
    M5.Display.setCursor(0, 60);

    M5.Display.print("種類: ");
    M5.Display.println(beverageType);
 
    M5.Display.print("飲んだ量: ");
    if (volume >= 0) {
        M5.Display.printf("%d ml\n", volume);
    } else {
        M5.Display.println("不明");
    }

    M5.Display.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Display.println(notes);
    } else {
        M5.Display.println("なし");
    }
}