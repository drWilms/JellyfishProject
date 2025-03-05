#ifndef SWTIMERMANAGER_H
#define SWTIMERMANAGER_H

#include "SWTimer.h"

#define MAX_TIMERS 10

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
    void pauseTimer(int timerID);
    void resumeTimer(int timerID);
    void resetTimer(int timerID);
    void changeInterval(int timerID, unsigned long newInterval);
};

#endif  // SWTIMERMANAGER_H
