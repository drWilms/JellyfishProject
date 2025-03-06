#include "JellyfishLEDs.h"

void JellyfishLEDs::init() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
}

void JellyfishLEDs::setLED(int index, int r, int g, int b) {
    if (index < NUM_LEDS) {
        leds[index] = CRGB(r, g, b);
        FastLED.show();
    }
}

void JellyfishLEDs::updateRainbow() {
    for (int i = 1; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 150);
    }
    hue += 2;  // Slowly shift hue
    FastLED.show();
}
