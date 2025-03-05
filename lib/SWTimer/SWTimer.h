#ifndef SWTIMER_H
#define SWTIMER_H

#include <Arduino.h>

class SWTimer {
private:
    unsigned long interval;
    unsigned long lastRun;
    bool enabled;
    bool paused;
    unsigned long pauseTime; // Stores when the timer was paused

public:
    SWTimer(unsigned long intervalMs);
    
    void start();
    void stop();
    void pause();
    void resume();
    void reset();
    void setInterval(unsigned long newInterval);
    
    bool isReady();
};

#endif  // SWTIMER_H
