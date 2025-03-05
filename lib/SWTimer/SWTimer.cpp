#include "SWTimer.h"

SWTimer::SWTimer(unsigned long intervalMs) {
    interval = intervalMs;
    lastRun = 0;
    enabled = false;
    paused = false;
    pauseTime = 0;
}

void SWTimer::start() {
    enabled = true;
    paused = false;
    lastRun = millis();
}

void SWTimer::stop() {
    enabled = false;
}

void SWTimer::pause() {
    if (enabled && !paused) {
        paused = true;
        pauseTime = millis();
    }
}

void SWTimer::resume() {
    if (paused) {
        paused = false;
        lastRun += (millis() - pauseTime); // Adjust lastRun to account for the pause duration
    }
}

void SWTimer::reset() {
    lastRun = millis();
}

void SWTimer::setInterval(unsigned long newInterval) {
    interval = newInterval;
}

bool SWTimer::isReady() {
    if (!enabled || paused) return false;

    if (millis() - lastRun >= interval) {
        lastRun = millis();
        return true;
    }
    return false;
}
