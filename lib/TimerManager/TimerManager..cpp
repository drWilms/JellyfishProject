#include "TimerManager.h"

// ======== TIMER CLASS ========
Timer::Timer(unsigned long interval, void (*callback)())
    : interval(interval), lastRun(0), callback(callback) {}

bool Timer::shouldRun() const {
    return (millis() - lastRun) >= interval;
}

void Timer::reset() {
    lastRun = millis();
}

void Timer::execute() {
    if (shouldRun() && callback) {
        callback();
        reset();
    }
}

// ======== TIMER MANAGER ========
TimerManager::TimerManager() : timerCount(0) {}

TimerManager::~TimerManager() {
    for (int i = 0; i < timerCount; i++) {
        delete timers[i];  // Prevent memory leaks
    }
}

void TimerManager::addTimer(unsigned long interval, void (*callback)()) {
    if (timerCount < MAX_TIMERS) {
        timers[timerCount++] = new Timer(interval, callback);
    }
}

void TimerManager::update() {
    for (int i = 0; i < timerCount; i++) {
        timers[i]->execute();
    }
}

// ======== HIGH/MID/LOW SPEED TIMERS ========
HighSpeedTimer::HighSpeedTimer() : TimerManager() {}
MidSpeedTimer::MidSpeedTimer() : TimerManager() {}
LowSpeedTimer::LowSpeedTimer() : TimerManager() {}
