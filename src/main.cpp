#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("[TEST] Minimal setup running...");
}

void loop() {
    Serial.println("[TEST] Still running...");
    delay(1000);
}
