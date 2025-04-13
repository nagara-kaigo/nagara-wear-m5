#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

class AudioRecorder; // 前方宣言
extern AudioRecorder recorder;

void startBackgroundTasks();
void stopBackgroundTasks();

#endif // TASK_MANAGER_H