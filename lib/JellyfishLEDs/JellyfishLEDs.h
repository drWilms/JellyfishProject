#ifndef JELLYFISHLEDS_H
#define JELLYFISHLEDS_H

#include <FastLED.h>
#include "config.h"

class JellyfishLEDs {
private:
    CRGB leds[NUM_LEDS];

public:
    JellyfishLEDs();
    void init();
    void setSingleColor(int index, CRGB color);
    void runRainbow();
};

#endif // JELLYFISHLEDS_H
