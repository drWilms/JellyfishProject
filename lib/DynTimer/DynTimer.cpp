#include "DynTimer.h"

std::vector<DynTimer> DynTimer::activeTimers;

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> cb, bool repeat)
    : interval(intervalMs), callback(cb), repeating(repeat) {
    nextExecution = millis() + interval;
}

void DynTimer::start() {
    nextExecution = millis() + interval;
}

bool DynTimer::isReady() {
    if (millis() >= nextExecution) {
        callback();
        if (repeating) {
            reset();
        }
        return true;
    }
    return false;
}

void DynTimer::reset() {
    nextExecution = millis() + interval;
}

void DynTimer::addTimer(unsigned long intervalMs, std::function<void()> cb, bool repeat) {
    activeTimers.emplace_back(intervalMs, cb, repeat);
}

void DynTimer::update() {
    for (auto it = activeTimers.begin(); it != activeTimers.end();) {
        if (it->isReady()) {
            if (!it->repeating) {
                it = activeTimers.erase(it);  // Remove one-time timers
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}
