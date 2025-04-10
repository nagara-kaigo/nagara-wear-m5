#include "screen_roading.h"
#include <FS.h>
#include <SD.h>

void showRoadingScreen(const AppState &state){
    M5.Lcd.setRotation(1);

    // 画面全体を白で塗りつぶし
    M5.Lcd.fillScreen(WHITE);
  
    // テキスト色を紺色に設定（背景は白）
    // NAVY が定義されていない場合は 0x001F (青) や 0x780F (紺寄り) などを使ってください
    M5.Lcd.setTextColor(NAVY, WHITE);
  
    // テキストの基準位置を「中央」に設定
    M5.Lcd.setTextDatum(MC_DATUM);

    M5.Lcd.setTextSize(2);

  
    // ディスプレイ中央に「ながらかいご」を描画
    M5.Lcd.drawString("ながらかいご", M5.Lcd.width() / 2, M5.Lcd.height() / 2);


    M5.Lcd.setTextSize(1);

}

