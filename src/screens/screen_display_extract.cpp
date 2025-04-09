#include "screen_display_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      
#include <ArduinoJson.h>  
#include "extracts/template_food_extract.h"


#define BACKGROUND_COLOR WHITE
#define TEXT_COLOR       BLACK
#define TITLE_COLOR      RED

void showRecordFromJson(const String &jsonString, const AppState &state) {
    StaticJsonDocument<512> doc;
    // JSON文字列をパース
    DeserializationError error = deserializeJson(doc, jsonString);

    // 画面クリア
    M5.Lcd.clear();
    M5.Lcd.fillScreen(BACKGROUND_COLOR);

    if (error) {
        // パースエラー時の画面表示
        M5.Lcd.clear();
        M5.Lcd.fillScreen(BACKGROUND_COLOR);
        M5.Lcd.setTextColor(TITLE_COLOR, BACKGROUND_COLOR);
        showHeaderBar("Error");
        M5.Lcd.println("Failed to parse JSON:");
        M5.Lcd.println(error.c_str());
        showFooterBar(state);
        return;
    }

    // ヘッダー表示（タイトル）
    M5.Lcd.setTextColor(TITLE_COLOR, BACKGROUND_COLOR);
    showHeaderBar(
        recordTypeToString(state.selectedRecordType) + "の記録"
        + state.selectedResident.givenName);   

    switch ( state.selectedRecordType ) {
    case MEAL:
        showFoodRecordFromJson(doc);
        break;
    case BATH:
        // showBathRecordFromJson(doc);
        break;
    }
    // フッター表示
    showFooterBar(state);
}
