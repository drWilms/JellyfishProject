#include "SWTimer.h"

SWTimer::SWTimer(unsigned long intervalMs) {
    interval = intervalMs;
    lastRun = millis();
    running = false;
}

void SWTimer::start() {
    lastRun = millis();
    running = true;
}

bool SWTimer::expired() {
    if (!running) return false;
    return (millis() - lastRun >= interval);
}
