#ifndef JELLYFISH_LEDS_H
#define JELLYFISH_LEDS_H

#include <FastLED.h>
#include "config.h"  // ✅ Ensure LED settings come from config

class JellyfishLEDs {
public:
    JellyfishLEDs();
    void begin();
    void startEffect(int pattern, int duration, int brightness);
    void clearEffect();  // ✅ Clear LEDs properly after effect

private:
    CRGB leds[NUM_LEDS];  // ✅ Using `NUM_LEDS` from config.h
};

#endif // JELLYFISH_LEDS_H
