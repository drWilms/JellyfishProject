#include "MidSpeedTimer.h"

MidSpeedTimer::MidSpeedTimer() {
    for (int i = 0; i < MAX_MSTIMERS; i++) {
        tasks[i].active = false;
    }
}

void MidSpeedTimer::addTask(unsigned long interval, void (*callback)()) {
    for (int i = 0; i < MAX_MSTIMERS; i++) {
        if (!tasks[i].active) {
            tasks[i].interval = interval;
            tasks[i].nextRun = millis() + interval;
            tasks[i].callback = callback;
            tasks[i].active = true;
            return;
        }
    }
}

void MidSpeedTimer::update() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_MSTIMERS; i++) {
        if (tasks[i].active && now >= tasks[i].nextRun) {
            tasks[i].callback();
            tasks[i].nextRun = now + tasks[i].interval;
        }
    }
}

void MidSpeedTimer::removeTask(void (*callback)()) {
    for (int i = 0; i < MAX_MSTIMERS; i++) {
        if (tasks[i].callback == callback) {
            tasks[i].active = false;
            return;
        }
    }
}
