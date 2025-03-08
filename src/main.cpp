#include <Arduino.h>
#include "config.h"
#include "DynTimer.h"

void toggleOnboardLED() {
    static bool ledState = false;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.printf("Toggling Onboard LED at %lu ms\n", millis());
}

void printMessage() {
    Serial.printf("Message printed at %lu ms\n", millis());
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    // Add timers dynamically
    DynTimer::addTimer(1000, toggleOnboardLED, true);  // LED every 1 sec
    DynTimer::addTimer(500, printMessage, true);       // Message every 500ms

    Serial.println("DynTimer Multi-Timer Test Started");
}

void loop() {
    DynTimer::update();  // Check and execute active timers
}
