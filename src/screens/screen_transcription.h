#ifndef SCREEN_TRANSCRIPTION_H
#define SCREEN_TRANSCRIPTION_H

struct AppState; // 前方宣言

void showTranscriptionScreen(const AppState &state);
void toggleRecording();
void rebootTranscriptionScreen(const AppState &state);

#endif
