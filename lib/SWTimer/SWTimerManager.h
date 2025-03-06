#ifndef SWTIMERMANAGER_H
#define SWTIMERMANAGER_H

#include "SWTimer.h"
#include <vector>
#include <functional>

class SWTimerManager {
private:
    struct TimerEntry {
        SWTimer* timer;
        std::function<void()> callback;
    };
    std::vector<TimerEntry> timers;

public:
    void addTimer(SWTimer& timer, std::function<void()> callback);
    void update();
};

#endif // SWTIMERMANAGER_H