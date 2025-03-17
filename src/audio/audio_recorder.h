#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <Arduino.h>
#include <driver/i2s.h>
#include "../system/sd_handler.h"

#define BUFFER_SIZE (16000 * 2 * 8)

class AudioRecorder {
public:
    AudioRecorder();
    ~AudioRecorder();

    void startRecording();
    void stopRecording();
    bool isRecording() const;
    void initialize();

private:
    static void recordTask(void* param);
    
    uint8_t* audioRingBuffer;
    uint8_t* tempBuffer;
    volatile size_t writeIndex;
    volatile size_t readIndex;
    SemaphoreHandle_t ringBufferMutex;
    bool recording;
    File recordingFile;
    TaskHandle_t recordingTaskHandle;
    static const i2s_port_t I2S_PORT = I2S_NUM_0;
};

#endif