// ========================= SWTimer.h =========================
#ifndef SW_TIMER_H
#define SW_TIMER_H

#include <Arduino.h>

class SWTimer {
private:
    unsigned long interval;
    unsigned long lastRun;
    bool running;

public:
    SWTimer(unsigned long intervalMs);
    void start();
    void update();
    bool expired();
};

#endif // SW_TIMER_H
