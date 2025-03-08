// ========================= TimerManager.cpp =========================
#include "TimerManager.h"

/** Timer Class Implementation */
Timer::Timer(unsigned long interval, std::function<void()> callback)
    : interval(interval), lastRun(millis()), callback(callback) {}

void Timer::check() {
    if (millis() - lastRun >= interval) {
        lastRun = millis();
        callback();
    }
}

void Timer::reset() {
    lastRun = millis();
}

unsigned long Timer::getInterval() const {
    return interval;
}

/** TimerManager Implementation */
void TimerManager::addTimer(unsigned long interval, std::function<void()> callback) {
    timers.emplace_back(interval, callback);
}

void TimerManager::update() {
    for (auto& timer : timers) {
        timer.check();
    }
}