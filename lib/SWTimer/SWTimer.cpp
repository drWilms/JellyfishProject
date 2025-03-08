// ========================= SWTimer.cpp =========================
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

void SWTimer::update() {
    if (running && millis() - lastRun >= interval) {
        running = false;
    }
}

bool SWTimer::expired() {
    return !running;
}
