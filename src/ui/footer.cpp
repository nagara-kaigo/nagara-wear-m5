#include "footer.h"
#include <M5Unified.h>

void showFooterBar(const AppState &state) {
    M5.Display.fillRect(0, 200, 320, 40, TFT_WHITE);
    M5.Display.drawLine(10, 210, 310, 210, TFT_BLACK);
    M5.Display.setTextDatum(textdatum_t::middle_right);
    M5.Display.drawString("戻る", 80, 225);
    M5.Display.setTextDatum(textdatum_t::middle_center);
    M5.Display.drawString("ホーム", 160, 225);
    M5.Display.setTextDatum(textdatum_t::middle_left);
    M5.Display.drawString("メニュー", 240, 225);
}


void showFooterBarRecording(const AppState &state) {
    M5.Display.fillRect(0, 200, 320, 40, TFT_WHITE);
    M5.Display.drawLine(10, 210, 310, 210, TFT_BLACK);
    M5.Display.setTextDatum(textdatum_t::middle_right);
    M5.Display.drawString("取消", 80, 225);
    M5.Display.setTextDatum(textdatum_t::middle_center);
    M5.Display.drawString("確定", 160, 225);
    M5.Display.setTextDatum(textdatum_t::middle_left);
    M5.Display.drawString("メニュー", 240, 225);
}


void showFooterBarCompleted(const AppState &state) {
    M5.Display.fillRect(0, 200, 320, 40, TFT_WHITE);
    M5.Display.drawLine(10, 210, 310, 210, TFT_BLACK);
    M5.Display.setTextDatum(textdatum_t::middle_center);
    M5.Display.drawString("終了（ホームに戻る）", 160, 225);
}