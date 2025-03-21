#include "audio_handler.h"
#include "audio_recorder.h"

static AudioRecorder* recorder = nullptr;

void initializeAudioRecorder() {
    if (recorder == nullptr) {
        recorder = new AudioRecorder();
    }
}

void startRecording() {
    if (recorder) recorder->startRecording();
}

void stopRecording() {
    if (recorder) recorder->stopRecording();
}

bool isRecording() {
    return recorder ? recorder->isRecording() : false;
}
