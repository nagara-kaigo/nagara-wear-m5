#include "screen_transcription.h"
#include <M5Unified.h>
#include "main.h"
#include "../ui/header.h"
#include "../ui/footer.h"
#include "task_manager.h"
#include "../audio/audio_recorder.h"
#include "screen_display_extract.h"
#include "../services/api/api.h"

extern AudioRecorder recorder;
extern MyApi api;

static String transcriptionText = "";
static bool isRecording = recorder.isRecording();

void updateTranscriptionText(const String& newText) {
    transcriptionText = newText;
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setCursor(10, 10);
    M5.Display.setTextColor(TFT_BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print(transcriptionText);
}

void toggleRecording() {
    if (!isRecording) {
        isRecording = true;
        startBackgroundTasks(); // task_managerでタスクを開始
    } else {
        isRecording = false;
        stopBackgroundTasks(); // task_managerでタスクを停止
    }
}

void showTranscriptionScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setCursor(10, 10);
    Serial.println(state.mealTime);
    showHeaderBar(recordTypeToString(state.selectedRecordType) + "のレコーディング中");
    showRecordFromJson(state, api.getRecordExtract());
    showFooterBarRecording(state);
    toggleRecording();
}

void rebootTranscriptionScreen(const AppState &state) {
    M5.Display.clear();
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setCursor(10, 10);
    M5.Display.setTextColor(TFT_BLACK);
    showHeaderBar(mealTimeToString(state.mealTime) + "レコーディング中");
    showRecordFromJson(state, api.getRecordExtract());
    showFooterBarRecording(state);
}
