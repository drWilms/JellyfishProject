#include "SWTimerManager.h"

SWTimerManager::SWTimerManager() {
    timerCount = 0;
}

int SWTimerManager::addTimer(unsigned long intervalMs) {
    if (timerCount >= MAX_TIMERS) return -1;
    timers[timerCount] = new SWTimer(intervalMs);
    return timerCount++;
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

void SWTimerManager::pauseTimer(int timerID) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->pause();
    }
}

void SWTimerManager::resumeTimer(int timerID) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->resume();
    }
}

void SWTimerManager::resetTimer(int timerID) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->reset();
    }
}

void SWTimerManager::changeInterval(int timerID, unsigned long newInterval) {
    if (timerID >= 0 && timerID < timerCount) {
        timers[timerID]->setInterval(newInterval);
    }
}
