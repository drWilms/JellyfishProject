#include "DynTimer.h"
#include <Arduino.h>

std::vector<DynTimer*> DynTimer::activeTimers; // Store timers globally

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating)
    : interval(intervalMs), callback(callback), repeating(repeating), running(true) {
    nextExecution = millis() + interval;
}

void DynTimer::start() {
    running = true;
    nextExecution = millis() + interval;
}

void DynTimer::pause() {
    if (running) {
        pauseRemaining = nextExecution - millis();
        running = false;
        Serial.printf("Timer PAUSED at %lu ms\n", millis());
    }
}

void DynTimer::resume() {
    if (!running) {
        nextExecution = millis() + pauseRemaining;
        running = true;
        Serial.printf("Timer RESUMED at %lu ms\n", millis());
    }
}

bool DynTimer::isReady() {
    if (!running) return false;  // Ensure execution stops when paused
    if (millis() >= nextExecution) {
        callback();
        if (repeating) {
            nextExecution = millis() + interval;  // Reset next execution time
        }
        return true;
    }
    return false;
}

void DynTimer::reset() {
    nextExecution = millis() + interval;
}

void DynTimer::addTimer(DynTimer* timer) {
    activeTimers.push_back(timer); // Dynamically add timers
}

void DynTimer::update() {
    for (auto it = activeTimers.begin(); it != activeTimers.end();) {
        DynTimer* timer = *it;
        if (timer->isReady()) {
            if (!timer->repeating) {
                it = activeTimers.erase(it); // Remove non-repeating timers
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}
