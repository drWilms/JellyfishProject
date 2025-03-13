#ifndef JELLYFISHLEDS_H
#define JELLYFISHLEDS_H

#include <FastLED.h>
#include "config.h"

#define DEBUG 1
#define LOG(x) if (DEBUG) Serial.println(F(x))

class JellyfishLEDs {
public:
    CRGB leds[NUM_LEDS];

    JellyfishLEDs();
    void setSingleColor(int index, CRGB color);
    void updateLEDs();
};

#endif
