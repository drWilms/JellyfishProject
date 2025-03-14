#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "Arduino.h"
#include "DynTimer.h"

#define MAX_FAST_TIMERS 5
#define MAX_MEDIUM_TIMERS 5
#define MAX_SLOW_TIMERS 5

typedef void (*TimerCallback)();

class TimerManager {
private:
    DynTimer fastTimers[MAX_FAST_TIMERS];  // ✅ **Nieuw**
    TimerCallback fastCallbacks[MAX_FAST_TIMERS];
    unsigned long fastDurations[MAX_FAST_TIMERS];

    DynTimer mediumTimers[MAX_MEDIUM_TIMERS];
    TimerCallback mediumCallbacks[MAX_MEDIUM_TIMERS];
    unsigned long mediumDurations[MAX_MEDIUM_TIMERS];

    DynTimer slowTimers[MAX_SLOW_TIMERS];
    TimerCallback slowCallbacks[MAX_SLOW_TIMERS];
    unsigned long slowDurations[MAX_SLOW_TIMERS];

public:
    TimerManager();
    
    int startFastTimer(unsigned long duration, TimerCallback callback);  // ✅ **Nieuw**
    int startMediumTimer(unsigned long duration, TimerCallback callback);
    int startSlowTimer(unsigned long duration, TimerCallback callback);
    
    void updateTimers();
};

#endif // TIMERMANAGER_H
