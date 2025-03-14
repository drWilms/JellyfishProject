#include "DynTimer.h"

DynTimer::DynTimer() : interval(0), lastRun(0), active(false) {}

void DynTimer::start(unsigned long duration) {
    interval = duration;
    lastRun = millis();
    active = true;
}

void DynTimer::stop() {
    active = false;
}

bool DynTimer::isExpired() {
    if (!active) return false;
    return (millis() - lastRun) >= interval;
}

bool DynTimer::isActive() const {
    return active;
}
