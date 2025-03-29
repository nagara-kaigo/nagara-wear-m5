#include "screen_standby.h"


void showStandbyScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    String user = state.selectedUser;
    showHeaderBar("利用者:" + user);
    M5.Lcd.setTextDatum(3);


    int rectWidth  = 80;     // 幅
    int rectHeight = 80;     // 高さ
    int gap        = 10;     // 四角同士の間隔
    int startX     = 40;     // 一番左の四角の描画開始X座標
    int startY     = 80;     // 四角の描画開始Y座標

    // テキストを中央揃えするための Datum 設定
    M5.Lcd.setTextDatum(MC_DATUM); // 中心を基準にテキストを描画

    // 1つ目の四角
    int x1 = startX;
    M5.Lcd.drawRect(x1, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("朝食", x1 + rectWidth/2, startY + rectHeight/2);

    // 2つ目の四角
    int x2 = x1 + rectWidth + gap;
    M5.Lcd.drawRect(x2, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("昼食", x2 + rectWidth/2, startY + rectHeight/2);

    // 3つ目の四角
    int x3 = x2 + rectWidth + gap;
    M5.Lcd.drawRect(x3, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("夕食", x3 + rectWidth/2, startY + rectHeight/2);


    showFooterBar(state);
}

bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state) {
    // ボタン共通のサイズと配置
    int rectWidth  = 80;
    int rectHeight = 80;
    int gap        = 10;
    int startX     = 40;
    int startY     = 80;

    // 各ボタンの範囲
    int x1 = startX;
    int x2 = x1 + rectWidth + gap;
    int x3 = x2 + rectWidth + gap;

    // REC1 の判定
    if (touch.x > x1 && touch.x < x1 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = "朝食";
        return true;
    }

    // REC2 の判定
    if (touch.x > x2 && touch.x < x2 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = "昼食";
        return true;
    }

    // REC3 の判定
    if (touch.x > x3 && touch.x < x3 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = "夕食";
        return true;
    }

    // どのボタンも押されていない
    return false;
}