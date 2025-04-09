#include "screen_display_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      
#include <ArduinoJson.h>  


#define BACKGROUND_COLOR WHITE
#define TEXT_COLOR       BLACK
#define TITLE_COLOR      RED

void showRecordFromJson(const String &jsonString, const AppState &state) {
    
    StaticJsonDocument<512> doc;

    // JSON文字列をパース
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        // パースエラー時の画面表示
        M5.Lcd.clear();
        M5.Lcd.fillScreen(BACKGROUND_COLOR);
        M5.Lcd.setTextColor(TITLE_COLOR, BACKGROUND_COLOR);
        showHeaderBar("Error");
        M5.Lcd.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
        M5.Lcd.setCursor(0, 60);
        M5.Lcd.println("Failed to parse JSON:");
        M5.Lcd.println(error.c_str());
        showFooterBar(state);
        return;
    }

    
    int  mainCourse = doc["mainCoursePercentage"] | -1;
    int  sideDish   = doc["sideDishPercentage"]   | -1;
    int  soup       = doc["soupPercentage"]       | -1;
    const char* beverageType = doc["beverageType"] | "UNKNOWN";
    int  beverageVolume      = doc["beverageVolume"] | -1;
    const char* notes        = doc["notes"]          | "";

    // 画面クリア
    M5.Lcd.clear();
    M5.Lcd.fillScreen(BACKGROUND_COLOR);

    // ヘッダー表示（タイトル）
    M5.Lcd.setTextColor(TITLE_COLOR, BACKGROUND_COLOR);
    showHeaderBar("食事記録" + state.selectedResident.givenName);   
    M5.Lcd.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    M5.Lcd.setCursor(0, 60);

    // 主食
    M5.Lcd.print("主食: ");
    if (mainCourse >= 0) {
        M5.Lcd.print("|");
        int barLength = mainCourse / 10;  // 100% なら =10個
        for (int i = 0; i < barLength; i++) {
            M5.Lcd.print("=");
        }
        M5.Lcd.print("| ");
        M5.Lcd.printf("(%d%%)\n", mainCourse);
        M5.Lcd.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    } else {
        M5.Lcd.println("不明");
    }

    // 副菜
    M5.Lcd.print("副菜: ");
    if (sideDish >= 0) {
        M5.Lcd.print("|");
        int barLength = sideDish / 10;
        for (int i = 0; i < barLength; i++) {
            M5.Lcd.print("=");
        }
        M5.Lcd.print("| ");
        M5.Lcd.printf("(%d%%)\n", sideDish);
        M5.Lcd.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
    } else {
        M5.Lcd.println("不明");
    }

    // 汁物
    M5.Lcd.print("汁物: ");
    if (soup >= 0) {
        M5.Lcd.print("|");
        int barLength = soup / 10;
        for (int i = 0; i < barLength; i++) {
            M5.Lcd.print("=");
        }
        M5.Lcd.print("| ");
        M5.Lcd.printf("(%d%%)\n", soup);
    } else {
        M5.Lcd.println("不明");
    }

    // 飲み物の種類
    M5.Lcd.print("飲み物種類: ");
    M5.Lcd.println(beverageType);

    // 飲んだ量
    M5.Lcd.print("飲んだ量: ");
    if (beverageVolume >= 0) {
        M5.Lcd.printf("%d ml\n", beverageVolume);
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

    // フッター表示
    showFooterBar(state);
}
