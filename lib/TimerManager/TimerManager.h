#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <Arduino.h>

class Timer {
private:
    unsigned long interval;
    unsigned long lastRun;
    void (*callback)();

public:
    Timer(unsigned long interval, void (*callback)());
    bool shouldRun() const;
    void reset();
    void execute();
};

class TimerManager {
protected:
    static const int MAX_TIMERS = 10;
    Timer* timers[MAX_TIMERS];
    int timerCount;

public:
    TimerManager();
    ~TimerManager();  // Destructor to prevent memory leaks
    void addTimer(unsigned long interval, void (*callback)());
    void update();
};

// Tiered Timer Managers
class HighSpeedTimer : public TimerManager {
public:
    HighSpeedTimer();
};

class MidSpeedTimer : public TimerManager {
public:
    MidSpeedTimer();
};

class LowSpeedTimer : public TimerManager {
public:
    LowSpeedTimer();
};

#endif  // TIMERMANAGER_H
