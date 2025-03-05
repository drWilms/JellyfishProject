#include "SWTimerManager.h"

SWTimerManager::SWTimerManager() {
    timerCount = 0;
}

int SWTimerManager::addTimer(unsigned long intervalMs) {
    if (timerCount >= MAX_TIMERS) return -1;  // Too many timers

    timers[timerCount] = new SWTimer(intervalMs);
    return timerCount++;  // Return the new timer ID
}

bool SWTimerManager::isReady(int timerID) {
    if (timerID < 0 || timerID >= timerCount) return false;
    return timers[timerID]->isReady();
}

void SWTimerManager::startTimer(int timerID) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->start();
    }
}

void SWTimerManager::stopTimer(int timerID) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->stop();
    }
}
