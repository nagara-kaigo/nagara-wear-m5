#include "audio_recorder.h"

static AudioRecorder recorder;

void initializeAudioRecorder() {
    // コンストラクタで `initialize()` が自動的に呼ばれるため、特に処理は不要
}

void startRecording() {
    recorder.startRecording();
}

void stopRecording() {
    recorder.stopRecording();
}

bool isRecording() {
    return recorder.isRecording();
}
