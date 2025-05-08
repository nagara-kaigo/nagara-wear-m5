#include "screen_standby.h"
#include "main.h"
#include "../ui/header.h"
#include "../ui/footer.h"

void showStandbyScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK, TFT_WHITE);
    String type = recordTypeToString(state.selectedRecordType);
    String title = state.selectedResident.familyName + state.selectedResident.givenName + "の" + type + "を記録";
    showHeaderBar(title);
    M5.Display.setTextDatum(textdatum_t::middle_center);

    switch (state.selectedRecordType)
    {
    case MEAL:{
        // 1つ目の四角
        int x1 = MEALTIME_STARTX;
        M5.Display.drawRect(x1, MEALTIME_STARTY, MEALTIME_RECTWIDTH, MEALTIME_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("朝食", x1 + MEALTIME_RECTWIDTH/2, MEALTIME_STARTY + MEALTIME_RECTHEIGHT/2);

        // 2つ目の四角
        int x2 = x1 + MEALTIME_RECTWIDTH + GAP;
        M5.Display.drawRect(x2, MEALTIME_STARTY, MEALTIME_RECTWIDTH, MEALTIME_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("昼食", x2 + MEALTIME_RECTWIDTH/2, MEALTIME_STARTY + MEALTIME_RECTHEIGHT/2);

        // 3つ目の四角
        int x3 = x2 + MEALTIME_RECTWIDTH + GAP;
        M5.Display.drawRect(x3, MEALTIME_STARTY, MEALTIME_RECTWIDTH, MEALTIME_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("夕食", x3 + MEALTIME_RECTWIDTH/2, MEALTIME_STARTY + MEALTIME_RECTHEIGHT/2);
        break;
    }
    
    case DRINK:{
        M5.Display.drawRect(CENTER_STARTX, CENTER_STARTY, CENTER_RECTWIDTH, CENTER_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("REC", CENTER_STARTX + CENTER_RECTWIDTH/2, CENTER_STARTY + CENTER_RECTHEIGHT/2);
        break;
    }

    case EXCRETION:{
        M5.Display.drawRect(CENTER_STARTX, CENTER_STARTY, CENTER_RECTWIDTH, CENTER_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("REC", CENTER_STARTX + CENTER_RECTWIDTH/2, CENTER_STARTY + CENTER_RECTHEIGHT/2);
        break;
    }

    case BATH:{
        M5.Display.drawRect(CENTER_STARTX, CENTER_STARTY, CENTER_RECTWIDTH, CENTER_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("REC", CENTER_STARTX + CENTER_RECTWIDTH/2, CENTER_STARTY + CENTER_RECTHEIGHT/2);
        break;
    }

    case EVERYDAY:{
        M5.Display.drawRect(CENTER_STARTX, CENTER_STARTY, CENTER_RECTWIDTH, CENTER_RECTHEIGHT, TFT_BLACK);
        M5.Display.drawString("REC", CENTER_STARTX + CENTER_RECTWIDTH/2, CENTER_STARTY + CENTER_RECTHEIGHT/2);
        break;
    }
    default:{
        Serial.println("error::RECORDTYPE is undefined");
        break;
    }
    }
    showFooterBar(state);
}

bool handleRecBtnTouch(const lgfx::v1::touch_point_t& touch, AppState &state) {
    switch (state.selectedRecordType)
    {
    case MEAL:{
        // 各ボタンの範囲
        int x1 = MEALTIME_STARTX;
        int x2 = x1 + MEALTIME_RECTWIDTH + GAP;
        int x3 = x2 + MEALTIME_RECTWIDTH + GAP;

        // REC1 の判定
        if (touch.x > x1 && touch.x < x1 + MEALTIME_RECTWIDTH &&
            touch.y > MEALTIME_STARTY && touch.y < MEALTIME_STARTY + MEALTIME_RECTHEIGHT) {
            state.mealTime = BREAKFAST;
            return true;
        }

        // REC2 の判定
        if (touch.x > x2 && touch.x < x2 + MEALTIME_RECTWIDTH &&
            touch.y > MEALTIME_STARTY && touch.y < MEALTIME_STARTY + MEALTIME_RECTHEIGHT) {
            state.mealTime = LUNCH;
            return true;
        }

        // REC3 の判定
        if (touch.x > x3 && touch.x < x3 + MEALTIME_RECTWIDTH &&
            touch.y > MEALTIME_STARTY && touch.y < MEALTIME_STARTY + MEALTIME_RECTHEIGHT) {
            state.mealTime = DINNER;
            return true;
        }

        // どのボタンも押されていない
        return false;
    }
    
    case DRINK:{
       if (touch.x > CENTER_STARTX && touch.x < CENTER_STARTX + CENTER_RECTWIDTH &&
           touch.y > CENTER_STARTY && touch.y < CENTER_STARTY + CENTER_RECTHEIGHT){
           return true;
           }
        return false;
    }

    case EXCRETION:{
        if (touch.x > CENTER_STARTX && touch.x < CENTER_STARTX + CENTER_RECTWIDTH &&
            touch.y > CENTER_STARTY && touch.y < CENTER_STARTY + CENTER_RECTHEIGHT){
            return true;
            }
        return false;
    }

    case BATH:{
        if (touch.x > CENTER_STARTX && touch.x < CENTER_STARTX + CENTER_RECTWIDTH &&
            touch.y > CENTER_STARTY && touch.y < CENTER_STARTY + CENTER_RECTHEIGHT){
            return true;
            }
        return false;
    }

    case EVERYDAY:{
        if (touch.x > CENTER_STARTX && touch.x < CENTER_STARTX + CENTER_RECTWIDTH &&
            touch.y > CENTER_STARTY && touch.y < CENTER_STARTY + CENTER_RECTHEIGHT){
            return true;
            }
        return false;
    }
    default:{
        Serial.println("error::RECORDTYPE is undefined");
        return false;
    }
    }
}