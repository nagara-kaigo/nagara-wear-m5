#include "screen_manager.h"

extern AppState appState;

void changeScreen(Screen newScreen) {
  appState.currentScreen = newScreen;

  switch (newScreen) {
    case USER_PICKER:
      showUserPickerScreen(appState);
      break;
    case STANDBY:
      showStandbyScreen(appState);
      break;
    case RECORDING:
      showRecordingScreen(appState);
      break;
    case TRANSCRIPTION:
      showTranscriptionScreen(appState);
      break;
  }
}