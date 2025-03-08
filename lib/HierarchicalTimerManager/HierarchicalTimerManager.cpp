
// ========================= HierarchicalTimerManager.cpp =========================
#include "HierarchicalTimerManager.h"

void HierarchicalTimerManager::addSlowTimer(SWTimer timer, std::function<void()> callback) {
    slowTimers.emplace_back(timer, callback);
}

void HierarchicalTimerManager::addFastTimer(SWTimer timer, std::function<void()> callback) {
    fastTimers.emplace_back(timer, callback);
}

void HierarchicalTimerManager::addUltraFastTimer(SWTimer timer, std::function<void()> callback) {
    ultraFastTimers.emplace_back(timer, callback);
}

void HierarchicalTimerManager::update() {
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