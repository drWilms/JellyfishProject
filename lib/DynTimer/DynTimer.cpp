#include "DynTimer.h"
#include <Arduino.h>

std::vector<DynTimer*> DynTimer::activeTimers;

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating)
    : interval(intervalMs), callback(callback), repeating(repeating), running(false), nextExecution(0) {}

void DynTimer::start() {
    running = true;
    nextExecution = millis() + interval;
    Serial.printf("[Timer] Started, next expiration: %lu\n", nextExecution);
}

void DynTimer::stop() {
    running = false;
    Serial.println("[Timer] Stopped.");
}

void DynTimer::pause() {
    if (running) {
        running = false;
        Serial.println("[Timer] Paused.");
    }
}

void DynTimer::resume() {
    if (!running) {
        running = true;
        nextExecution = millis() + interval;
        Serial.println("[Timer] Resumed.");
    }
}

bool DynTimer::isReady() {
    if (!running) return false;
    return millis() >= nextExecution;
}

void DynTimer::reset() {
    nextExecution = millis() + interval;
}

void DynTimer::update() {
    if (isReady()) {
        callback();
        if (repeating) {
            reset();
        } else {
            stop();
        }
    }
}

void DynTimer::updateAll() {
    for (auto it = activeTimers.begin(); it != activeTimers.end();) {
        DynTimer* timer = *it;
        if (timer->isReady()) {
            timer->update();
            if (!timer->repeating) {
                it = activeTimers.erase(it);
                continue;
            }
        }
        ++it;
    }
}
