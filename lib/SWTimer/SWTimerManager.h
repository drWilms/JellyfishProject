#ifndef SWTIMERMANAGER_H
#define SWTIMERMANAGER_H

#include "SWTimer.h"

#define MAX_TIMERS 10  // Adjust based on project needs

class SWTimerManager {
private:
    SWTimer* timers[MAX_TIMERS];
    int timerCount;

public:
    SWTimerManager();
    int addTimer(unsigned long intervalMs);
    bool isReady(int timerID);
    void startTimer(int timerID);
    void stopTimer(int timerID);
};

#endif  // SWTIMERMANAGER_H
