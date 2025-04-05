#include "screen_pick_resident.h"

void showResidentPickerScreen(AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    showHeaderBar("利用者を選んでください");
    M5.Lcd.setTextDatum(3);

    size_t totalResidents = state.selectedResidentGivenName.size();
    Serial.println(totalResidents);
    state.totalResidentPage = (totalResidents/6)+1;
    Serial.println(state.totalResidentPage);
    size_t startIdx = state.currentResidentPage * 6;
    size_t endIdx = min(startIdx + 6, totalResidents);
    size_t j = 0;

    // 利用者をページ単位で表示
    for(size_t i = startIdx; i < endIdx; i++){
        if((i % 2) == 0){
            M5.Lcd.drawRect(BOX_LEFT_X, BOX_START_Y + (BOX_INTERVAL_Y * j), BOX_WIDTH, BOX_HEIGHT, BLACK);
            M5.Lcd.drawString(state.selectedResidentGivenName[i], BOX_LEFT_X + TEXT_OFFSET_X, BOX_START_Y + TEXT_OFFSET_Y + (BOX_INTERVAL_Y * j));
        }
        else{
            M5.Lcd.drawRect(BOX_RIGHT_X, BOX_START_Y + (BOX_INTERVAL_Y * j), BOX_WIDTH, BOX_HEIGHT, BLACK);
            M5.Lcd.drawString(state.selectedResidentGivenName[i], BOX_RIGHT_X + TEXT_OFFSET_X, BOX_START_Y + TEXT_OFFSET_Y + (BOX_INTERVAL_Y * j));
            j++;
        }
    }

    // ページに応じて矢印を表示
    if (state.totalResidentPage > 1 && state.currentResidentPage < state.totalResidentPage - 1) {
        // 右矢印（次ページあり）
        M5.Lcd.fillTriangle(ARROW_RIGHT_X1, ARROW_Y_CENTER, ARROW_RIGHT_X2, ARROW_Y_TOP, ARROW_RIGHT_X2, ARROW_Y_BOTTOM, BLACK);
    }

    if (state.totalResidentPage > 1 && state.currentResidentPage > 0) {
        // 左矢印（前ページあり）
        M5.Lcd.fillTriangle(ARROW_LEFT_X1, ARROW_Y_CENTER, ARROW_LEFT_X2, ARROW_Y_TOP, ARROW_LEFT_X2, ARROW_Y_BOTTOM, BLACK);
    }

    showFooterBar(state);
}


bool handleResidentPickerTouch(const TouchPoint_t &touch, AppState &state) {
    size_t j = 0;

    size_t totalResidents = state.selectedResidentGivenName.size();
    size_t startIdx = state.currentResidentPage * 6;
    size_t endIdx = min(startIdx + 6, totalResidents);

    for(size_t i = startIdx; i < endIdx; i++) {
        int x1, y1, x2, y2;

        if((i % 2) == 0) {
            x1 = BOX_LEFT_X;
            y1 = BOX_START_Y + (BOX_INTERVAL_Y * j);
            x2 = x1 + BOX_WIDTH;
            y2 = y1 + BOX_HEIGHT;
        } else {
            x1 = BOX_RIGHT_X;
            y1 = BOX_START_Y + (BOX_INTERVAL_Y * j);
            x2 = x1 + BOX_WIDTH;
            y2 = y1 + BOX_HEIGHT;
            j++;
        }

        if (touch.x >= x1 && touch.x <= x2 &&
            touch.y >= y1 && touch.y <= y2) {
            state.selectedUser = state.selectedResidentGivenName[i];
            return true;
        }
    }

    // 左矢印のタッチ判定 (前ページへ)
    if(state.totalResidentPage > 1 && state.currentResidentPage > 0 &&
       touch.x >= ARROW_LEFT_X1 && touch.x <= ARROW_LEFT_X2 &&
       touch.y >= ARROW_Y_TOP && touch.y <= ARROW_Y_BOTTOM) {
        state.currentResidentPage--;
        Serial.println("前ページへ");
        showResidentPickerScreen(state);
        //return true;
    }

    // 右矢印のタッチ判定 (次ページへ)
    if(state.totalResidentPage > 1 && state.currentResidentPage < state.totalResidentPage - 1 &&
       touch.x >= ARROW_RIGHT_X2 && touch.x <= ARROW_RIGHT_X1 &&
       touch.y >= ARROW_Y_TOP && touch.y <= ARROW_Y_BOTTOM) {
        state.currentResidentPage++;
        Serial.println("次ページへ");
        showResidentPickerScreen(state);
        //return true;
    }

    return false;
}
