#include "SWTimer.h"

SWTimer::SWTimer(unsigned long intervalMs) {
    interval = intervalMs;
    lastRun = 0;
    enabled = false;
}

void SWTimer::start() {
    enabled = true;
    lastRun = millis();
}

void SWTimer::stop() {
    enabled = false;
}

bool SWTimer::isReady() {
    if (!enabled) return false;

    if (millis() - lastRun >= interval) {
        lastRun = millis();
        return true;
    }
    return false;
}
