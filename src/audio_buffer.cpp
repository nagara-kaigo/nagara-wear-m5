#include "audio_buffer.h"

uint8_t* audioRingBuffer = nullptr;
SemaphoreHandle_t ringBufferMutex;
volatile size_t writeIndex = 0;
volatile size_t readIndex  = 0;

void initializeAudioBuffer() {
    audioRingBuffer = (uint8_t*) ps_malloc(BUFFER_SIZE);
    if (!audioRingBuffer) {
        Serial.println("Failed to allocate buffer in PSRAM!");
        while(1);
    }
    ringBufferMutex = xSemaphoreCreateMutex();
    if (ringBufferMutex == NULL) {
        Serial.println("Failed to create ringBuffer mutex!");
        while(1);
    }
}

void writeToRingBuffer(uint8_t* buffer, size_t bytesRead) {
    if (xSemaphoreTake(ringBufferMutex, (TickType_t)10) == pdTRUE) {
        for (size_t i = 0; i < bytesRead; i++) {
            audioRingBuffer[writeIndex] = buffer[i];
            writeIndex = (writeIndex + 1) % BUFFER_SIZE;
        }
        xSemaphoreGive(ringBufferMutex);
    }
}

size_t readFromRingBuffer(uint8_t* buffer, size_t bufferSize) {
    size_t available = 0;
    if (xSemaphoreTake(ringBufferMutex, (TickType_t)100) == pdTRUE) {
        size_t currentWriteIndex = writeIndex;
        available = (currentWriteIndex + BUFFER_SIZE - readIndex) % BUFFER_SIZE;
        for (size_t i = 0; i < available && i < bufferSize; i++) {
            buffer[i] = audioRingBuffer[readIndex];
            readIndex = (readIndex + 1) % BUFFER_SIZE;
        }
        xSemaphoreGive(ringBufferMutex);
    }
    return available;
}