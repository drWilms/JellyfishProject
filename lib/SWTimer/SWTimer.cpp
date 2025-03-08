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
        lastRun = millis();  // Reset timer instead of stopping it
    }
}


bool SWTimer::expired() {
    return !running;
}
