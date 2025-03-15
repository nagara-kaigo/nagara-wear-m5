#ifndef WHISPER_CLIENT_H
#define WHISPER_CLIENT_H

#include <WiFiClientSecure.h>
#include <string>

void transcribeAudio(const char* filename);

#endif