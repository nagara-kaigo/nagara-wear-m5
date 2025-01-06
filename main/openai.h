#ifndef OPENAI_H
#define OPENAI_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

#define API_URL_STT "https://api.openai.com/v1/audio/transcriptions"

bool sendAudioFile(const String &filePath, String &response);

#endif // API_UTILS_H
