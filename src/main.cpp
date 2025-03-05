#include "config.h"  // Ensure this is included FIRST
#include <Arduino.h>
#include "macros.inc"

void setup() {
    Serial.begin(115200);
    LOG("Jellyfish Project Starting...");

    // Test LED Pin (if available)
    pinMode(PIN_LED, OUTPUT);   // This should now be recognized
    digitalWrite(PIN_LED, HIGH);
    WAIT(500);
    digitalWrite(PIN_LED, LOW);
}

void loop() {
    LOG("Running...");
    WAIT(1000);
}
