#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <stdint.h>

#define MAX_TIMERS 10  // Adjustable per tier

struct TimerTask {
    uint32_t interval;
    uint32_t lastRun;
    void (*callback)();
};

class TimerManager {
protected:
    TimerTask timers[MAX_TIMERS];
    uint8_t numTimers = 0;

public:
    void addTimer(uint32_t interval, void (*callback)());
    void update();
};

// **Specialized Timer for FastLED-style animations**
class HighSpeedTimer {
public:
    void update();
};

class MidSpeedTimer : public TimerManager {};
class LowSpeedTimer : public TimerManager {};

#endif
