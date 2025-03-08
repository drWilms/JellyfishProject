#ifndef DYNTIMER_H
#define DYNTIMER_H

#include <Arduino.h>
#include <functional>
#include <vector>

class DynTimer {
private:
    unsigned long interval;
    unsigned long nextExecution;
    std::function<void()> callback;
    bool repeating;

    static std::vector<DynTimer> activeTimers;

public:
    DynTimer(unsigned long intervalMs, std::function<void()> cb, bool repeat = true);
    
    void start();
    bool isReady();
    void reset();
    
    static void addTimer(unsigned long intervalMs, std::function<void()> cb, bool repeat = true);
    static void update();
};

#endif // DYNTIMER_H
