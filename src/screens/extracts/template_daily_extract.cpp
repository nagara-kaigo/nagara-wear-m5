#include "template_bath_extract.h"
#include "screen_manager.h"
#include <M5Unified.h>      

void showDailyRecordFromJson(const JsonDocument& doc) {
    const char* dailyStatus = doc["dailyStatus"] | "Unknown";
    const char* notes = doc["notes"] | "";
 
    M5.Display.setTextColor(BLACK);
    M5.Display.setCursor(0, 60);

    M5.Display.print("状態: ");
    M5.Display.println(dailyStatus);
 
    M5.Display.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Display.println(notes);
    } else {
        M5.Display.println("なし");
    }
}
