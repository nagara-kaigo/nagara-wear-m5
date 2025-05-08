#include "template_food_extract.h"
#include "../../ui/header.h"
#include "../../ui/footer.h"
#include <M5Unified.h>      
#include <ArduinoJson.h>  

void showFoodRecordFromJson(const JsonDocument& doc) {
    int  mainCourse = doc["mainCoursePercentage"] | -1;
    int  sideDish   = doc["sideDishPercentage"]   | -1;
    int  soup       = doc["soupPercentage"]       | -1;
    const char* beverageType = doc["beverageType"] | "UNKNOWN";
    int  beverageVolume      = doc["beverageVolume"] | -1;
    const char* notes        = doc["notes"]          | "";

    M5.Display.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    M5.Display.setCursor(0, 60);

    // 主食
    M5.Display.print("主食: ");
    if (mainCourse >= 0) {
        M5.Display.print("|");
        int barLength = mainCourse / 10;  // 100% なら =10個
        for (int i = 0; i < barLength; i++) {
            M5.Display.print("=");
        }
        M5.Display.print("| ");
        M5.Display.printf("(%d%%)\n", mainCourse);
        M5.Display.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    } else {
        M5.Display.println("不明");
    }

    // 副菜
    M5.Display.print("副菜: ");
    if (sideDish >= 0) {
        M5.Display.print("|");
        int barLength = sideDish / 10;
        for (int i = 0; i < barLength; i++) {
            M5.Display.print("=");
        }
        M5.Display.print("| ");
        M5.Display.printf("(%d%%)\n", sideDish);
        M5.Display.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    } else {
        M5.Display.println("不明");
    }

    // 汁物
    M5.Display.print("汁物: ");
    if (soup >= 0) {
        M5.Display.print("|");
        int barLength = soup / 10;
        for (int i = 0; i < barLength; i++) {
            M5.Display.print("=");
        }
        M5.Display.print("| ");
        M5.Display.printf("(%d%%)\n", soup);
    } else {
        M5.Display.println("不明");
    }

    // 飲み物の種類
    M5.Display.print("飲み物種類: ");
    M5.Display.println(beverageType);

    // 飲んだ量
    M5.Display.print("飲んだ量: ");
    if (beverageVolume >= 0) {
        M5.Display.printf("%d ml\n", beverageVolume);
    } else {
        M5.Display.println("不明");
    }

    // 特記事項
    M5.Display.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Display.println(notes);
    } else {
        M5.Display.println("なし");
    }
}