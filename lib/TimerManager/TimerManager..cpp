#include "TimerManager.h"
#include <Arduino.h>  // Required for millis()

void TimerManager::addTimer(uint32_t interval, void (*callback)()) {
    if (numTimers < MAX_TIMERS) {
        timers[numTimers].interval = interval;
        timers[numTimers].lastRun = millis();
        timers[numTimers].callback = callback;
        numTimers++;
    }
}

void TimerManager::update() {
    uint32_t now = millis();
    for (uint8_t i = 0; i < numTimers; i++) {
        if (now - timers[i].lastRun >= timers[i].interval) {
            timers[i].lastRun = now;
            timers[i].callback();
        }
    }
}

// **FastLED-style HighSpeedTimer (runs continuously)**
void HighSpeedTimer::update() {
    static uint8_t brightness = 0;
    static int8_t direction = 1;

    brightness += direction;
    if (brightness == 255 || brightness == 0) direction *= -1;

    // Replace with actual FastLED code
    // leds[0] = CHSV(160, 255, brightness);
    // FastLED.show();
}
