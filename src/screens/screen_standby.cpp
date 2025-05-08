#include "screen_standby.h"

String recordTypeToString(RecordType type) {
    switch (type) {
        case MEAL:       return "食事";
        case DRINK:      return "水分";
        case EXCRETION:  return "排泄";
        case BATH:       return "入浴";
        case EVERYDAY:   return "日常";
        default:         return "";
    }
}

void showStandbyScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK, TFT_WHITE);
    String type = recordTypeToString(state.selectedRecordType);
    showHeaderBar("利用者:" + state.selectedResident.givenName + "  記録:" + type);
    M5.Display.setTextDatum(textdatum_t::middle_left);

    // テキストを中央揃えするための Datum 設定
    M5.Display.setTextDatum(textdatum_t::middle_center); // 中心を基準にテキストを描画

    // 1つ目の四角
    int x1 = STARTX;
    M5.Display.drawRect(x1, STARTY, RECTWIDTH, RECTHEIGHT, TFT_BLACK);
    M5.Display.drawString("朝食", x1 + RECTWIDTH/2, STARTY + RECTHEIGHT/2);

    // 2つ目の四角
    int x2 = x1 + RECTWIDTH + GAP;
    M5.Display.drawRect(x2, STARTY, RECTWIDTH, RECTHEIGHT, TFT_BLACK);
    M5.Display.drawString("昼食", x2 + RECTWIDTH/2, STARTY + RECTHEIGHT/2);

    // 3つ目の四角
    int x3 = x2 + RECTWIDTH + GAP;
    M5.Display.drawRect(x3, STARTY, RECTWIDTH, RECTHEIGHT, TFT_BLACK);
    M5.Display.drawString("夕食", x3 + RECTWIDTH/2, STARTY + RECTHEIGHT/2);

    showFooterBar(state);
}

bool handleRecBtnTouch(const lgfx::v1::touch_point_t& touch, AppState &state) {
    // ボタン共通のサイズと配置

    // 各ボタンの範囲
    int x1 = STARTX;
    int x2 = x1 + RECTWIDTH + GAP;
    int x3 = x2 + RECTWIDTH + GAP;

    // REC1 の判定
    if (touch.x > x1 && touch.x < x1 + RECTWIDTH &&
        touch.y > STARTY && touch.y < STARTY + RECTHEIGHT) {
        state.mealTime = BREAKFAST;
        return true;
    }

    // REC2 の判定
    if (touch.x > x2 && touch.x < x2 + RECTWIDTH &&
        touch.y > STARTY && touch.y < STARTY + RECTHEIGHT) {
        state.mealTime = LUNCH;
        return true;
    }

    // REC3 の判定
    if (touch.x > x3 && touch.x < x3 + RECTWIDTH &&
        touch.y > STARTY && touch.y < STARTY + RECTHEIGHT) {
        state.mealTime = DINNER;
        return true;
    }

    // どのボタンも押されていない
    return false;
}