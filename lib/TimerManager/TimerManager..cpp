
#include "TimerManager.h"
#include <Arduino.h>

// Constructor
TimerManager::TimerManager() {
    for (int i = 0; i < MAX_FAST_TIMERS; i++) {
        fastDurations[i] = 0;
        fastCallbacks[i] = nullptr;
    }
    for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
        mediumDurations[i] = 0;
        mediumCallbacks[i] = nullptr;
    }
    for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
        slowDurations[i] = 0;
        slowCallbacks[i] = nullptr;
    }
}

// ✅ **Nieuwe functie voor Fast Timers**
int TimerManager::startFastTimer(unsigned long duration, TimerCallback callback) {
    for (int i = 0; i < MAX_FAST_TIMERS; i++) {
        if (!fastTimers[i].isActive()) {
            fastTimers[i].start(duration);
            fastCallbacks[i] = callback;
            fastDurations[i] = duration;
            Serial.printf("✅ Fast timer gestart op index %d met duur %lu ms.\n", i, duration);
            return i;
        }
    }
    Serial.println("❌ GEEN VRIJE FAST TIMERS BESCHIKBAAR!");
    return -1;
}

// ✅ **Medium en Slow Timers blijven zoals eerder gedefinieerd**
int TimerManager::startMediumTimer(unsigned long duration, TimerCallback callback) {
    for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
        if (!mediumTimers[i].isActive()) {
            mediumTimers[i].start(duration);
            mediumCallbacks[i] = callback;
            mediumDurations[i] = duration;
            Serial.printf("✅ Medium timer gestart op index %d met duur %lu ms.\n", i, duration);
            return i;
        }
    }
    Serial.println("❌ GEEN VRIJE MEDIUM TIMERS BESCHIKBAAR!");
    return -1;
}

int TimerManager::startSlowTimer(unsigned long duration, TimerCallback callback) {
    for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
        if (!slowTimers[i].isActive()) {
            slowTimers[i].start(duration);
            slowCallbacks[i] = callback;
            slowDurations[i] = duration;
            Serial.printf("✅ Slow timer gestart op index %d met duur %lu ms.\n", i, duration);
            return i;
        }
    }
    Serial.println("❌ GEEN VRIJE SLOW TIMERS BESCHIKBAAR!");
    return -1;
}

// ✅ **Update alle timers (Fast, Medium, Slow)**
void TimerManager::updateTimers() {
    for (int i = 0; i < MAX_FAST_TIMERS; i++) {
        if (fastTimers[i].isExpired() && fastCallbacks[i] != nullptr) {
            Serial.printf("⏳ Fast timer %d verlopen, roep callback aan.\n", i);
            fastCallbacks[i]();
            Serial.printf("🔄 Fast timer %d herstart met %lu ms.\n", i, fastDurations[i]);  
            fastTimers[i].start(fastDurations[i]);
        }
    }
    for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
        if (mediumTimers[i].isExpired() && mediumCallbacks[i] != nullptr) {
            Serial.printf("⏳ Medium timer %d verlopen, roep callback aan.\n", i);
            mediumCallbacks[i]();
            Serial.printf("🔄 Medium timer %d herstart met %lu ms.\n", i, mediumDurations[i]);  
            mediumTimers[i].start(mediumDurations[i]);
        }
    }
    for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
        if (slowTimers[i].isExpired() && slowCallbacks[i] != nullptr) {
            Serial.printf("⏳ Slow timer %d verlopen, roep callback aan.\n", i);
            slowCallbacks[i]();
            Serial.printf("🔄 Slow timer %d herstart met %lu ms.\n", i, slowDurations[i]);  
            slowTimers[i].start(slowDurations[i]);
        }
    }
}
