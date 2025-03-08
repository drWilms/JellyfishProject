#include "DynTimer.h"
#include <Arduino.h>
#include <macros.inc>
#include "config.h"

bool ledState = false;  // LED state tracker
unsigned long startDelay = 10000;  // Initial delay of 10s
unsigned long pauseTime = 5000;    // Pause duration after blinking starts

DynTimer* ledTimer;
DynTimer* pauseTimer;

bool isPaused = false;


void toggleLED() {
    if (!isPaused) {  
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        Serial.printf("[DynTimer] LED %s at %lu ms\n", ledState ? "ON" : "OFF", millis());

        // Adjust timing for 1s ON, 2s OFF
        if (ledState) {
            ledTimer->reset(1000);  // 1s ON
        } else {
            ledTimer->reset(2000);  // 2s OFF
        }
    }
}

void pauseLED() {
    Serial.printf("[DynTimer] Pausing LED at %lu ms\n", millis());
    isPaused = true;
    digitalWrite(LED_PIN, LOW); // Ensure LED stays OFF during pause
    pauseTimer->start(pauseTime);  // Start the pause timer
}

void resumeLED() {
    Serial.printf("[DynTimer] Resuming LED at %lu ms\n", millis());
    isPaused = false;
    ledTimer->reset(1000); // Restart with the ON phase
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);  // Ensure LED starts OFF

    Serial.printf("[DynTimer] Waiting %lu ms before starting LED blinking...\n", startDelay);
    delay(startDelay); // Initial 10s delay

    ledTimer = new DynTimer(1000, toggleLED, true);
    pauseTimer = new DynTimer(0, resumeLED, false); // Will be triggered later

    Serial.printf("[DynTimer] LED blinking started at %lu ms\n", millis());

    // Schedule pause after 5 seconds of blinking
    DynTimer* pauseTrigger = new DynTimer(5000, pauseLED, false);
}

void loop() {
    DynTimer::update();
}