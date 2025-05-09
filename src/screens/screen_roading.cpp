#include "screen_roading.h"
#include <M5Unified.h>

void showRoadingScreen(const AppState &state){
    M5.Display.setRotation(1);

    // 画面全体を白で塗りつぶし
    M5.Display.fillScreen(TFT_WHITE);
  
    // テキスト色を紺色に設定（背景は白）
    // NAVY が定義されていない場合は 0x001F (青) や 0x780F (紺寄り) などを使ってください
    M5.Display.setTextColor(TFT_NAVY, TFT_WHITE);
  
    // テキストの基準位置を「中央」に設定
    M5.Display.setTextDatum(textdatum_t::middle_center);

    M5.Display.setTextSize(2);

  
    // ディスプレイ中央に「ながらかいご」を描画
    M5.Display.drawString("ながらかいご", M5.Display.width() / 2, M5.Display.height() / 2);


    M5.Display.setTextSize(1);
}

