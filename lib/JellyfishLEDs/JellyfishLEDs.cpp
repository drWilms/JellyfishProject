#include "JellyfishLEDs.h"

JellyfishLEDs::JellyfishLEDs() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
}

void JellyfishLEDs::init() {
    FastLED.clear();
    FastLED.show();
}

void JellyfishLEDs::setSingleColor(int index, CRGB color) {
    if (index >= 0 && index < NUM_LEDS) {
        leds[index] = color;
        FastLED.show();
    }
}

void JellyfishLEDs::runRainbow() {
    static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 255);
    }
    FastLED.show();
    hue += 5;
}