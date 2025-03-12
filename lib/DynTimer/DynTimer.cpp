#include "DynTimer.h"
#include <Arduino.h>

// ======================== DynTimer Implementation ========================

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating)
    : interval(intervalMs), callback(callback), repeating(repeating), running(false), nextExecution(0), debugEnabled(false) {}

void DynTimer::start() {
    running = true;
    nextExecution = millis() + interval;
}

void DynTimer::stop() {
    running = false;
}

void DynTimer::pause() {
    running = false;
}

void DynTimer::resume() {
    running = true;
    nextExecution = millis() + interval;
}

bool DynTimer::isReady() {
    return running && millis() >= nextExecution;
}

void DynTimer::reset() {
    nextExecution = millis() + interval;
}

void DynTimer::setInterval(unsigned long newInterval) {
    interval = newInterval;
    reset();
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

// ======================== TimerManager Implementation ========================

int TimerManager::addTimer(unsigned long interval, std::function<void()> callback, bool repeating) {
    DynTimer* timer = new DynTimer(interval, callback, repeating);
    timers.push_back(timer);
    timer->start();
    return timers.size() - 1;
}

void TimerManager::removeTimer(int index) {
    if (index >= 0 && index < timers.size()) {
        delete timers[index];
        timers.erase(timers.begin() + index);
    }
}

void TimerManager::updateAll() {
    for (auto& timer : timers) {
        timer->update();
    }
}

void TimerManager::stopAll() {
    for (auto& timer : timers) {
        delete timer;
    }
    timers.clear();
}

DynTimer* TimerManager::getTimer(int index) {
    if (index >= 0 && index < timers.size()) {
        return timers[index];
    }
    return nullptr;
}
