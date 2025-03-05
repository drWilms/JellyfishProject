#include "config.h"
#include "macros.inc"
#include "SWTimerManager.h"

SWTimerManager timerManager;
int timer1, timer2;

void setup() {
    Serial.begin(115200);
    LOG("Jellyfish Project - Timer Manager Starting...");

    // Add two timers: one triggers every 2s, another every 5s
    timer1 = timerManager.addTimer(2000);
    timer2 = timerManager.addTimer(5000);

    // Start both timers
    timerManager.startTimer(timer1);
    timerManager.startTimer(timer2);
}

void loop() {
    if (timerManager.isReady(timer1)) {
        LOG("Timer 1 Triggered (2s)");
    }

    if (timerManager.isReady(timer2)) {
        LOG("Timer 2 Triggered (5s)");
    }
}
