#include "DynTimer.h"
#include <Arduino.h>

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating)
    : interval(intervalMs), callback(callback), repeating(repeating), running(true), pauseRemaining(0) {
    nextExecution = millis() + interval;
}

void DynTimer::reset(unsigned long newInterval) {
    interval = newInterval;
    nextExecution = millis() + interval;
}

void DynTimer::start(unsigned long newInterval) {
    running = true;
    interval = newInterval;
    nextExecution = millis() + interval;
}


void DynTimer::pause() {
    if (running) {
        pauseRemaining = millis() < nextExecution ? nextExecution - millis() : interval; // Use interval if already overdue
        running = false;
        Serial.printf("[DynTimer] Timer PAUSED at %lu ms (remaining: %lu ms)\n", millis(), pauseRemaining);
    }
}


void DynTimer::resume() {
    if (!running) {
        nextExecution = millis() + pauseRemaining;
        running = true;
        Serial.printf("[DynTimer] Timer RESUMED at %lu ms, new execution at %lu ms\n", millis(), nextExecution);
    }
}

bool DynTimer::isReady() {
    if (!running) {
        return false;  // Skip execution if paused
    }

    if (millis() >= nextExecution) {
        Serial.printf("[DynTimer] Timer TRIGGERED at %lu ms\n", millis());
        if (callback) callback();
        if (repeating) {
            nextExecution = millis() + interval;
            Serial.printf("[DynTimer] Timer REPEATING, next execution at %lu ms\n", nextExecution);
        }
        return true;
    }
    return false;
}

void DynTimer::update() {
    for (DynTimer* timer : timersList) {  // Loop through internal timer list
        if (!timer->running) continue;
        if (timer->isReady()) timer->execute();
    }
}

