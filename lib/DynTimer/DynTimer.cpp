#include "DynTimer.h"
#include <Arduino.h>

// =========================================
// ========== DynTimer Implementatie =======
// =========================================

DynTimer::DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating)
    : interval(intervalMs), callback(callback), repeating(repeating), running(false), nextExecution(0), state(INACTIVE), debugEnabled(false) {}

void DynTimer::start() {
    running = true;
    state = ACTIVE;
    nextExecution = millis() + interval;
    if (debugEnabled) {
        Serial.printf("[DEBUG] Timer started with interval %lu ms, next execution at %lu ms\n", interval, nextExecution);
    }
}

void DynTimer::stop() {
    running = false;
    state = COMPLETED;
    if (debugEnabled) {
        Serial.println("[DEBUG] Timer stopped.");
    }
}

void DynTimer::pause() {
    running = false;
    state = INACTIVE;
    if (debugEnabled) {
        Serial.println("[DEBUG] Timer paused.");
    }
}

void DynTimer::resume() {
    running = true;
    state = ACTIVE;
    nextExecution = millis() + interval;
    if (debugEnabled) {
        Serial.printf("[DEBUG] Timer resumed, next execution at %lu ms\n", nextExecution);
    }
}

bool DynTimer::isReady() {
    if (this == nullptr) return false;  // 🚨 Voorkom crash bij null pointers
    if (!running) return false;
    return millis() >= nextExecution;
}



void DynTimer::reset() {
    nextExecution = millis() + interval;
    if (debugEnabled) {
        Serial.printf("[DEBUG] Timer reset, next execution at %lu ms\n", nextExecution);
    }
}
void DynTimer::update() {
    if (isReady()) {
        unsigned long startTime = millis();
        callback();  // 🚀 Voer de callback uit

        // 🚨 Controleer of de callback te lang duurt
        if (millis() - startTime > 50) {
            Serial.println("[WARNING] Timer callback duurde te lang!");
            delay(1);  // ESP de kans geven om andere taken uit te voeren
        }

        if (repeating) {
            reset();
            state = ACTIVE;
        } else {
            stop();
            state = COMPLETED;
        }
    }
}



void DynTimer::setInterval(unsigned long newInterval) {
    interval = newInterval;
    reset();
    if (debugEnabled) {
        Serial.printf("[DEBUG] Timer interval updated to %lu ms\n", newInterval);
    }
}

DynTimer::TimerState DynTimer::getState() const {
    return state;
}


void DynTimer::setDebug(bool enable) {
    debugEnabled = enable;
}

bool DynTimer::getDebug() const {
    return debugEnabled;
}

// =========================================
// ========= TimerManager Implementatie =====
// =========================================

int TimerManager::addTimer(unsigned long interval, std::function<void()> callback, bool repeating) {
    DynTimer* timer = new DynTimer(interval, callback, repeating);
    timers.push_back(timer);
    timer->start();
    return timers.size() - 1;
}

void TimerManager::removeTimer(DynTimer* timer) {
    for (auto it = timers.begin(); it != timers.end(); it++) {
        if (*it == timer) {
            delete *it;
            timers.erase(it);
            Serial.println("[DEBUG] Timer removed.");
            break;
        }
    }
}

void TimerManager::cleanupTimers() {
    for (auto it = timers.begin(); it != timers.end(); ) {
        if (*it == nullptr || (*it)->getState() == DynTimer::COMPLETED) {
            delete *it;
            it = timers.erase(it);  // ✅ Correcte manier om verwijdering te verwerken
        } else {
            ++it;
        }
    }
}



void TimerManager::updateAll() {
    unsigned long startTime = millis();  // ⏳ Tijd bijhouden
    int processed = 0;  // Teller om te beperken hoeveel timers we verwerken

    for (auto it = timers.begin(); it != timers.end(); ) {
        if (*it == nullptr) {  
            it = timers.erase(it);
            continue;
        }

        if ((*it)->isReady()) {
            Serial.printf("[DEBUG] Verwerken timer op index: %ld\n", std::distance(timers.begin(), it));
            
            (*it)->update();

            // 🚨 Als de timer zichzelf verwijdert, moet de iterator opnieuw gezet worden
            if (timers.empty()) break;  // Stop als er geen timers meer zijn
            it = timers.begin();  // Reset iterator om geheugenfouten te voorkomen
            continue;
        }

        ++it;

        // 🚨 Stop als we te veel timers verwerken in één keer
        if (processed > 10 || millis() - startTime > 50) {
            Serial.println("[WARNING] TimerManager::updateAll() is te zwaar, pauzeren...");
            break;
        }
    }
}




void TimerManager::stopAll() {
    for (auto& timer : timers) {
        delete timer;
    }
    timers.clear();
    Serial.println("[DEBUG] All timers stopped and cleared.");
}

DynTimer* TimerManager::getTimer(int index) {
    if (index >= 0 && index < timers.size()) {
        return timers[index];
    }
    return nullptr;
}

int TimerManager::getActiveTimerCount() {
    return timers.size();
}

void TimerManager::setDebug(bool enable) {
    debugEnabled = enable;
}

bool TimerManager::getDebug() const {
    return debugEnabled;
}


