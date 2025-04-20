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
SwipeState swipeState = SWIPE_NONE;

void handleTapTransition(const TouchPoint_t &touch, SwipeState swipeState) {

  /* ── メイン領域（y < 200） ───────────── */
  if (touch.y < 200) {
      switch (appState.currentScreen) {
          case RESIDENT_PICKER:
              if (handleResidentPickerTouch(touch, appState, swipeState)) {
                  changeScreen(RECORD_TYPE_PICKER);
              }
              break;

          case STANDBY:
              if (handleRecBtnTouch(touch, appState)) {
                  changeScreen(TRANSCRIPTION);
              }
              break;

          case RECORD_TYPE_PICKER:
              if (handleRecordTypeTouch(touch, appState)) {
                  changeScreen(STANDBY);
              }
              break;
      }
  }
  /* ── フッター領域 ──────────────────── */
  else {
      handleFooterTouch(touch);
  }
}

void handleTouchEvents() {

  static bool         prevPressed = false;
  static TouchPoint_t currentTouchPosition, firstTouchPosition;
  static size_t i = 0;


  bool isPressed = M5.Touch.ispressed();
  if (isPressed) {
    if(!prevPressed){
      firstTouchPosition = M5.Touch.getPressPoint();
      //ispressedとの同期
      if(firstTouchPosition == -1){
        return;
      }
    }
      //ispressedとの同期
      if(M5.Touch.getPressPoint().x != -1){
        currentTouchPosition = M5.Touch.getPressPoint();
        prevPressed = true;
      return ;
      }
  }
  if(prevPressed){
    int differentPosition = currentTouchPosition.x - firstTouchPosition.x;
    if(abs(differentPosition) >= SWIPE_RANGE){
      if(differentPosition < 0){
        swipeState = SWIPE_LEFT;
        Serial.println("SWIPE_LEFT");
      }
      else if(differentPosition > 0){
        Serial.println("SWIPE_RIGHT");
        swipeState = SWIPE_RIGHT;
      }
    }
    handleTapTransition(currentTouchPosition,swipeState);
    prevPressed = false;
    swipeState = SWIPE_NONE;
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