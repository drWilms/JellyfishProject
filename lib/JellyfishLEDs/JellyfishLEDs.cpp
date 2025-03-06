#include "JellyfishLEDs.h"
#include "FastLED.h"
#include "config.h"
#include "macros.inc"

JellyfishLEDs::JellyfishLEDs() {}

void JellyfishLEDs::begin() {
    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS);  // ✅ Now using config.h
    FastLED.clear();
    FastLED.show();
}

void JellyfishLEDs::startEffect(int pattern, int duration, int brightness) {
    LOG("LED Effect: Pattern = %d, Duration = %d ms, Brightness = %d", pattern, duration, brightness);


    FastLED.setBrightness(brightness);
    
    switch (pattern) {
        case 1:
            LOG("Turning LEDs Red");
            for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Red;
            break;
        case 2:
            LOG("Turning LEDs Blue");
            for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Blue;
            break;
        case 3:
            LOG("Turning LEDs Green");
            for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Green;
            break;
        default:
            LOG("Clearing LEDs");
            FastLED.clear();
    }

    FastLED.show();
    LOG("FastLED.show() called!");  
}

void JellyfishLEDs::clearEffect() {
    LOG("Clearing LEDs after effect duration.");
    FastLED.clear();
    FastLED.show();
}
