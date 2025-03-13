#ifndef LowSpeedTIMER_H
#define LowSpeedTIMER_H

#include <Arduino.h>

#define MAX_LSTIMERS 3  

class LowSpeedTimer {
private:
    struct TimerTask {
        unsigned long interval;
        unsigned long nextRun;
        void (*callback)();
        bool active;
    };

    TimerTask tasks[MAX_LSTIMERS];

public:
    LowSpeedTimer();
    void addTask(unsigned long interval, void (*callback)());
    void update();
    void removeTask(void (*callback)());
};

#endif  
