#ifndef SWTIMER_H
#define SWTIMER_H

#include <Arduino.h>

class SWTimer {
private:
    unsigned long interval;
    unsigned long lastRun;
    bool enabled;

public:
    SWTimer(unsigned long intervalMs);
    void start();
    void stop();
    bool isReady();
};

#endif  // SWTIMER_H
