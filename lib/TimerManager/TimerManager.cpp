
// ========================= TimerManager.cpp =========================
#include "TimerManager.h"

void TimerManager::addSlowTimer(SWTimer timer, std::function<void()> callback) {
    slowTimers.emplace_back(timer, callback);
}

void TimerManager::addFastTimer(SWTimer timer, std::function<void()> callback) {
    fastTimers.emplace_back(timer, callback);
}

void TimerManager::addUltraFastTimer(SWTimer timer, std::function<void()> callback) {
    ultraFastTimers.emplace_back(timer, callback);
}

void TimerManager::update() {
    for (auto& timerPair : slowTimers) {
        timerPair.first.update();
        if (timerPair.first.expired()) timerPair.second();
    }
    for (auto& timerPair : fastTimers) {
        timerPair.first.update();
        if (timerPair.first.expired()) timerPair.second();
    }
    for (auto& timerPair : ultraFastTimers) {
        timerPair.first.update();
        if (timerPair.first.expired()) timerPair.second();
    }
}