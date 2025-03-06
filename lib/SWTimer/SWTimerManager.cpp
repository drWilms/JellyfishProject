#include "SWTimerManager.h"

void SWTimerManager::addTimer(SWTimer& timer, std::function<void()> callback) {
    timers.push_back({&timer, callback});
}

void SWTimerManager::update() {
    for (auto& entry : timers) {
        if (entry.timer->expired()) {
            entry.callback();
            entry.timer->start();
        }
    }
}
