#ifndef DYNTIMER_H
#define DYNTIMER_H

#include <Arduino.h>
#include <functional>
#include <vector>

class DynTimer {
private:
    unsigned long interval;
    unsigned long nextExecution;
    unsigned long pauseRemaining = 0;
    bool repeating;
    bool running;
    std::function<void()> callback;

    static std::vector<DynTimer*> activeTimers; // Stores all timers

public:
    DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating = true);
    void start();
    void pause();
    void resume();
    bool isReady();
    void reset();

    static void addTimer(DynTimer* timer); // Restore this function
    static void update(); // Fix update function to work with stored timers
};

#endif // DYNTIMER_H
