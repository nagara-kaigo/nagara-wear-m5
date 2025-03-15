#include "screen_transcription.h"

void showTranscriptionScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    toggleRecording();
}