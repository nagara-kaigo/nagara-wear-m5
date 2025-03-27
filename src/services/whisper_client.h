#ifndef WHISPER_CLIENT_H
#define WHISPER_CLIENT_H
#include <SD.h>

void transcribeAudio();
void writeWavHeader(File file, int sampleRate, int bitsPerSample, int numChannels);
void updateWavHeader(File file);
String getHTTPJsonValue(const String& response, const String& key);
#endif