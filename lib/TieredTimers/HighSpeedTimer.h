#ifndef HIGHSPEEDTIMER_H
#define HIGHSPEEDTIMER_H

#include <Arduino.h>

#define MAX_HSTIMERS 5  

class HighSpeedTimer {
private:
    struct TimerTask {
        unsigned long interval;
        unsigned long nextRun;
        void (*callback)();
        bool active;
    };

    TimerTask tasks[MAX_HSTIMERS];

public:
    HighSpeedTimer();
    void addTask(unsigned long interval, void (*callback)());
    void update();
    void removeTask(void (*callback)());
};

#endif  
