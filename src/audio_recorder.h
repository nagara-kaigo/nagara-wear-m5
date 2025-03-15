#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <M5Core2.h>
#include <driver/i2s.h>

void initializeAudioRecorder();
void toggleRecording();
void task0(void* arg);
void task1(void* arg);
void writeWavHeader(File file, int sampleRate, int bitsPerSample, int numChannels);
void updateWavHeader(File file);

#endif