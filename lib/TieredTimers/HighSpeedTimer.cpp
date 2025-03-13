#include "HighSpeedTimer.h"

HighSpeedTimer::HighSpeedTimer() {
    for (int i = 0; i < MAX_HSTIMERS; i++) {
        tasks[i].active = false;
    }
}

void HighSpeedTimer::addTask(unsigned long interval, void (*callback)()) {
    for (int i = 0; i < MAX_HSTIMERS; i++) {
        if (!tasks[i].active) {
            tasks[i].interval = interval;
            tasks[i].nextRun = millis() + interval;
            tasks[i].callback = callback;
            tasks[i].active = true;
            return;
        }
    }
}

void HighSpeedTimer::update() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_HSTIMERS; i++) {
        if (tasks[i].active && now >= tasks[i].nextRun) {
            tasks[i].callback();
            tasks[i].nextRun = now + tasks[i].interval;
        }
    }
}

void HighSpeedTimer::removeTask(void (*callback)()) {
    for (int i = 0; i < MAX_HSTIMERS; i++) {
        if (tasks[i].callback == callback) {
            tasks[i].active = false;
            return;
        }
    }
}
