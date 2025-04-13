#define FOOTER_HOME_MIN_X 109
#define FOOTER_HOME_MAX_X 218

#include <M5Core2.h>
#include "touch_handler.h"
#include "screen_manager.h"
#include "screens/screen_transcription.h"

#include "screens/screen_pick_user.h"
#include "screens/screen_pick_resident.h"
#include "screens/screen_standby.h"
#include "screens/screen_transcription.h"
#include "screens/screen_display_extract.h"
#include "screens/screen_pick_record_type.h"

extern AppState appState;

void handleTouchEvents() {
  TouchPoint_t touch;
  
  if (!M5.Touch.ispressed()) {
    return;
  }

  touch = M5.Touch.getPressPoint();

  // メインコンテンツのタッチ
  if (touch.y < 200) {
    switch (appState.currentScreen) {
      case RESIDENT_PICKER:
        if (handleResidentPickerTouch(touch, appState)) {
          changeScreen(RECORD_TYPE_PICKER);
        }
        break;
      case STANDBY:
        if (handleRecBtnTouch(touch, appState)) {
          changeScreen(TRANSCRIPTION);
        }
        break;
      case RECORD_TYPE_PICKER:
        if(handleRecordTypeTouch(touch,appState)){
          changeScreen(STANDBY);
        }
    }
  } 
  // フッター部分のタッチ
  else {
    handleFooterTouch(touch);
  }
}

// フッター部分のタッチイベント処理
void handleFooterTouch(TouchPoint_t touch) {
    M5.Axp.SetLDOEnable(3, true);
    delay(75);
    M5.Axp.SetLDOEnable(3, false);
  if(appState.currentScreen == TRANSCRIPTION){
    Serial.println("currentScreen is TRANSCRIPTION");
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      toggleRecording();
      Serial.println("delay 700");
      M5.Lcd.fillRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, WHITE);
      M5.Lcd.drawRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, BLACK);
      M5.Lcd.drawString("保存しています",CENTER_STARTX - 10, CENTER_STARTY + (CENTER_RECTHEIGHT + 20) / 2);
      delay(700);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      toggleRecording();
      Serial.println("delay 700");
      M5.Lcd.fillRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, WHITE);
      M5.Lcd.drawRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, BLACK);
      M5.Lcd.drawString("取消しています",CENTER_STARTX - 10, CENTER_STARTY + (CENTER_RECTHEIGHT + 20) / 2);
      delay(700);
      changeScreen(RESIDENT_PICKER);
    }
  }
  else if (appState.currentScreen == EXTRACT){
    Serial.println("currentScreen is EXTRACT");
    changeScreen(RESIDENT_PICKER);
  }
  else{
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      changeScreen(RESIDENT_PICKER);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      popScreen();
    } else if (touch.x >= FOOTER_HOME_MAX_X){
      changeScreen(EXTRACT);
    }
  }
}