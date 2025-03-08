#ifndef DYNTIMER_H
#define DYNTIMER_H

#include <functional>

class DynTimer {
private:
    unsigned long interval;
    unsigned long nextExecution;
    std::function<void()> callback;
    bool repeating;
    bool running;
    unsigned long pauseRemaining;

public:
    DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating = true);
    void reset(unsigned long newInterval);
    void start(unsigned long newInterval);
    
    void pause();
    void resume();
    bool isReady();
 
    static void update();

};

#endif // DYNTIMER_H
