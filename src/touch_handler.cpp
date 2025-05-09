#define FOOTER_HOME_MIN_X 109
#define FOOTER_HOME_MAX_X 218

#include <M5Unified.h>
#include "touch_handler.h"
#include "screen_manager.h"
#include "screens/screen_transcription.h"
#include "main.h"

#include "screens/screen_pick_user.h"
#include "screens/screen_pick_resident.h"
#include "screens/screen_standby.h"
#include "screens/screen_transcription.h"
#include "screens/screen_display_extract.h"
#include "screens/screen_pick_record_type.h"

extern AppState appState;
SwipeState swipeState = NONE;

void handleTapTransition(const lgfx::v1::touch_point_t &touch, SwipeState swipeState) {
  /* ── メイン領域（y < 200） ───────────── */
  if (touch.y < 200) {
      switch (appState.currentScreen) {
          case PICK_RESIDENT:
              if (handleResidentPickerTouch(touch, appState, swipeState)) {
                  changeScreen(PICK_RECORD_TYPE);
              }
              break;

          case STANDBY:
              if (handleRecBtnTouch(touch, appState)) {
                  changeScreen(TRANSCRIPTION);
              }
              break;

          case PICK_RECORD_TYPE:
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
  if (!M5.Touch.isEnabled()) {
    return;
  }

  auto touch = M5.Touch.getDetail();

  static bool prevPressed = false;
  static lgfx::v1::touch_point_t currentTouchPosition, firstTouchPosition;
  static size_t i = 0;

  bool isPressed = M5.Touch.getCount() > 0;
  if (isPressed) {
    if(!prevPressed){
      firstTouchPosition = M5.Touch.getDetail();
      if(firstTouchPosition.x == -1){
        return;
      }
    }
    if(M5.Touch.getDetail().x != -1){
      currentTouchPosition = M5.Touch.getDetail();
      prevPressed = true;
      return;
    }
  }
  if(prevPressed){
    int differentPosition = currentTouchPosition.x - firstTouchPosition.x;
    if(abs(differentPosition) >= SWIPE_RANGE){
      if(differentPosition < 0){
        swipeState = LEFT;
        Serial.println("SWIPE_LEFT");
      }
      else if(differentPosition > 0){
        Serial.println("SWIPE_RIGHT");
        swipeState = RIGHT;
      }
    }
    handleTapTransition(currentTouchPosition, swipeState);
    prevPressed = false;
    swipeState = NONE;
  }
}

// フッター部分のタッチイベント処理
void handleFooterTouch(const lgfx::v1::touch_point_t& touch) {
  if(appState.currentScreen == TRANSCRIPTION){
    Serial.println("currentScreen is TRANSCRIPTION");
    delay(75);
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      toggleRecording();
      Serial.println("delay 700");
      M5.Display.fillRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, TFT_WHITE);
      M5.Display.drawRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, TFT_BLACK);
      M5.Display.drawString("保存しています",CENTER_STARTX - 10, CENTER_STARTY + (CENTER_RECTHEIGHT + 20) / 2);
      delay(700);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      toggleRecording();
      Serial.println("delay 700");
      M5.Display.fillRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, TFT_WHITE);
      M5.Display.drawRect(CENTER_STARTX-15, CENTER_STARTY, CENTER_RECTWIDTH + 30, CENTER_RECTHEIGHT + 20, TFT_BLACK);
      M5.Display.drawString("取消しています",CENTER_STARTX - 10, CENTER_STARTY + (CENTER_RECTHEIGHT + 20) / 2);
      delay(700);
      changeScreen(PICK_RESIDENT);
    }
  }
  else if (appState.currentScreen == EXTRACT){
    Serial.println("currentScreen is EXTRACT");
    changeScreen(PICK_RESIDENT);
  }
  else{
    delay(75);
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      changeScreen(PICK_RESIDENT);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      popScreen();
    } else if (touch.x >= FOOTER_HOME_MAX_X){
      changeScreen(EXTRACT);
    }
  }
}