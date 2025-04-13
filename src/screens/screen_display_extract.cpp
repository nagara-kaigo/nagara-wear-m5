#include <M5Core2.h>      
#include <ArduinoJson.h>  
#include "main.h" // AppState を参照
#include "screen_display_extract.h"
#include "extracts/template_food_extract.h"
#include "extracts/template_bath_extract.h"
#include "extracts/template_beverage_extract.h"
//#include "extracts/template_elimination_extract.h"
#include "extracts/template_daily_extract.h"
#include "../ui/header.h"
#include "../ui/footer.h"

#define BACKGROUND_COLOR WHITE
#define TEXT_COLOR       BLACK
#define TITLE_COLOR      RED

void showRecordFromJson(const String &jsonString, const AppState &state) {
    StaticJsonDocument<512> doc;
    //DynamicJsonDocument doc(1024); // 動的メモリ割り当てを使用
    Serial.println(jsonString);
    // JSON文字列をパース
    DeserializationError error = deserializeJson(doc, jsonString);

    // 画面クリア
    M5.Lcd.clear();
    M5.Lcd.fillScreen(BACKGROUND_COLOR);

    if (error) {
        Serial.print("JSON parse error: ");
        Serial.println(error.c_str());  // エラーメッセージをシリアルモニタに表示
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
    M5.Lcd.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);

    switch ( state.selectedRecordType ) {
    case MEAL:
        showFoodRecordFromJson(doc);
        break;
    case BATH:
        showBathRecordFromJson(doc);
        break;
    case DRINK:
        showBeverageRecordFromJson(doc);
        break;
    //case EXCRETION:
    //    showExcretionRecordFromJson(doc);
    //    break;
    case EVERYDAY:
        showDailyRecordFromJson(doc);
        break;
    }

    showHeaderBar(
        recordTypeToString(state.selectedRecordType) + "の記録"
        + state.selectedResident.givenName);   

    // フッター表示
    showFooterBar(state);
}
