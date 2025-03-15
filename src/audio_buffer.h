#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <M5Core2.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#define BUFFER_SIZE (16000 * 2 * 10)

extern uint8_t* audioRingBuffer;
extern SemaphoreHandle_t ringBufferMutex;
extern volatile size_t writeIndex;
extern volatile size_t readIndex;

void initializeAudioBuffer();
void writeToRingBuffer(uint8_t* buffer, size_t bytesRead);
size_t readFromRingBuffer(uint8_t* buffer, size_t bufferSize);

#endif