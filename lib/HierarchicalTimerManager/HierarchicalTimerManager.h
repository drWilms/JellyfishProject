// ========================= HierarchicalTimerManager.h =========================
#ifndef HIERARCHICALTIMERMANAGER_H
#define HIERARCHICALTIMERMANAGER_H

#include <vector>
#include <functional>
#include <Arduino.h>
#include "SWTimer.h"

class HierarchicalTimerManager {
private:
    std::vector<std::pair<SWTimer, std::function<void()>>> slowTimers;
    std::vector<std::pair<SWTimer, std::function<void()>>> fastTimers;
    std::vector<std::pair<SWTimer, std::function<void()>>> ultraFastTimers;

public:
    void addSlowTimer(SWTimer timer, std::function<void()> callback);
    void addFastTimer(SWTimer timer, std::function<void()> callback);
    void addUltraFastTimer(SWTimer timer, std::function<void()> callback);
    void update();
};

#endif // HIERARCHICALTIMERMANAGER_H