#include <Arduino.h>
#include "config.h"        // 🔥 Ensure NUM_LEDS is included BEFORE it's used
#include "JellyfishLEDs.h"

JellyfishLEDs::JellyfishLEDs(SWTimerManager* tm) {
    timerManager = tm;
    timerID = timerManager->addTimer(100); // Update LEDs every 100ms
    leds = new CRGB[NUM_LEDS];             // Dynamically allocate memory
}

JellyfishLEDs::~JellyfishLEDs() {
    delete[] leds;                         // Free allocated memory
}

void JellyfishLEDs::begin() {
    FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);  // 🔥 Ensure brightness is high
    FastLED.clear();
    FastLED.show();
}
void JellyfishLEDs::update() {
    Serial.println("Updating LEDs...");  // 🔥 Debug message to check if update() runs

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;  // 🔥 Force all LEDs to RED
    }
    FastLED.show();
}


