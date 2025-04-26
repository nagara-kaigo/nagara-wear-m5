#ifndef REALTIME_API_H
#define REALTIME_API_H
#include <WebSocketsClient.h>

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
void sendSessionUpdate();
void sendPcmChunk(const int16_t* data, size_t samples);

#endif