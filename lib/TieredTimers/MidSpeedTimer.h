#ifndef MIDSPEEDTIMER_H
#define MIDSPEEDTIMER_H

#include <Arduino.h>

#define MAX_MSTIMERS 3  

class MidSpeedTimer {
private:
    struct TimerTask {
        unsigned long interval;
        unsigned long nextRun;
        void (*callback)();
        bool active;
    };

    TimerTask tasks[MAX_MSTIMERS];

public:
    MidSpeedTimer();
    void addTask(unsigned long interval, void (*callback)());
    void update();
    void removeTask(void (*callback)());
};

#endif  
