#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "audio/audio_recorder.h"
extern AudioRecorder recorder;

void startBackgroundTasks();
void stopBackgroundTasks();

#endif // TASK_MANAGER_H