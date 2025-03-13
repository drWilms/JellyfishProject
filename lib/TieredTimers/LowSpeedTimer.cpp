#include "LowSpeedTimer.h"

LowSpeedTimer::LowSpeedTimer() {
    for (int i = 0; i < MAX_LSTIMERS; i++) {
        tasks[i].active = false;
    }
}

void LowSpeedTimer::addTask(unsigned long interval, void (*callback)()) {
    for (int i = 0; i < MAX_LSTIMERS; i++) {
        if (!tasks[i].active) {
            tasks[i].interval = interval;
            tasks[i].nextRun = millis() + interval;
            tasks[i].callback = callback;
            tasks[i].active = true;
            return;
        }
    }
}

void LowSpeedTimer::update() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_LSTIMERS; i++) {
        if (tasks[i].active && now >= tasks[i].nextRun) {
            tasks[i].callback();
            tasks[i].nextRun = now + tasks[i].interval;
        }
    }
}

void LowSpeedTimer::removeTask(void (*callback)()) {
    for (int i = 0; i < MAX_LSTIMERS; i++) {
        if (tasks[i].callback == callback) {
            tasks[i].active = false;
            return;
        }
    }
}
