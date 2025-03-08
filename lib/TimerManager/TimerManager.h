// ========================= TimerManager.h =========================
#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <vector>
#include <functional>
#include <Arduino.h>
#include "macros.inc"

class Timer {
private:
    unsigned long interval;
    unsigned long lastRun;
    std::function<void()> callback;

public:
    Timer(unsigned long interval, std::function<void()> callback);
    void check();
    void reset();
    unsigned long getInterval() const;
};

class TimerManager {
private:
    std::vector<Timer> timers;

public:
    void addTimer(unsigned long interval, std::function<void()> callback);
    void update();
};

#endif // TIMER_MANAGER_H
