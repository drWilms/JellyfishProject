#include <Arduino.h>
#include "DynTimer.h"
#include "config.h"

void toggleOnboardLED() {
    static bool state = false;
    state = !state;
    digitalWrite(LED_PIN, state);
    Serial.printf("Toggling Onboard LED at %lu ms\n", millis());
}

DynTimer ledTimer(1000, toggleOnboardLED, true); // Create LED timer

void setup() {
    Serial.begin(115200);
    Serial.println("DynTimer Multi-Timer Test Started");

    pinMode(LED_PIN, OUTPUT);

    DynTimer::addTimer(&ledTimer); // Register LED timer
}

void loop() {
    DynTimer::update(); // Properly check & execute timers
}
