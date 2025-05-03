#ifndef REALTIME_API_H
#define REALTIME_API_H
#include <WebSocketsClient.h>

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
void sendAudioData(const uint8_t* pcmData, size_t dataLen);

#endif