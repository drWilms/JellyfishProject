#include "JellyfishLEDs.h"
#include "JellyfishQueue.h"

JellyfishQueue ledQueue;

JellyfishLEDs::JellyfishLEDs() {}

void JellyfishLEDs::setSingleColor(int index, CRGB color) {
    if (index >= 0 && index < NUM_LEDS) {
        leds[index] = color;
        FastLED.show();
    }
}

void JellyfishLEDs::updateLEDs(int audioLevel) {
    int brightness = map(audioLevel, 0, 5000, 10, 255);
    brightness = constrain(brightness, 10, 255);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(160, 255, brightness);
    }
    FastLED.show();
}
void JellyfishLEDs::silentMode() {
    FastLED.clear();
    FastLED.show();
}

