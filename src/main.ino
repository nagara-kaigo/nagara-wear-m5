#include "recorder.h"
#include "network.h"

void setup() {
    initRecorder();
    initNetwork();
}

void loop() {
    recordAndSend();
    delay(1000);
}
