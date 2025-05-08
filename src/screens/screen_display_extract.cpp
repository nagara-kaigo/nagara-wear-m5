#include <M5Unified.h>      
#include <ArduinoJson.h>  
#include "main.h" // AppState を参照
#include "screen_display_extract.h"
#include "extracts/template_food_extract.h"
#include "extracts/template_bath_extract.h"
#include "extracts/template_beverage_extract.h"
#include "extracts/template_elimination_extract.h"
#include "extracts/template_daily_extract.h"
#include "../ui/header.h"
#include "../ui/footer.h"

#define BACKGROUND_COLOR TFT_WHITE
#define TEXT_COLOR       TFT_BLACK
#define TITLE_COLOR      TFT_RED

void showRecordFromJson(const AppState &state, const String &jsonString) {
    StaticJsonDocument<512> doc;

    // 画面クリア
    M5.Display.clear();
    M5.Display.fillScreen(BACKGROUND_COLOR);

    if (!jsonString.isEmpty()) {
        // JSON文字列をパース
        DeserializationError error = deserializeJson(doc, jsonString);
        if (error) {
            // パースエラー時の画面表示
            M5.Display.clear();
            M5.Display.fillScreen(BACKGROUND_COLOR);
            M5.Display.setTextColor(TITLE_COLOR, BACKGROUND_COLOR);
            showHeaderBar("Error");
            M5.Display.println("Failed to parse JSON:");
            M5.Display.println(error.c_str());
            showFooterBar(state);
            return;
        }
    }

    // ヘッダー表示（タイトル）
    M5.Display.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);

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
    case EXCRETION:
        showEliminationRecordFromJson(doc);
        break;
    case EVERYDAY:
        showDailyRecordFromJson(doc);
        break;
    }

    showHeaderBar(
        recordTypeToString(state.selectedRecordType) + "の記録"
        + state.selectedResident.givenName);   

    // フッター表示
    if(state.currentScreen == EXTRACT){
        showFooterBarCompleted(state);
    }else if (state.currentScreen == TRANSCRIPTION){
        showFooterBarRecording(state);
    }
}
