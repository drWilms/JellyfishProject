#ifndef JELLYFISHLEDS_H
#define JELLYFISHLEDS_H

#include <FastLED.h>
#include "config.h"

class JellyfishLEDs {
public:
    void init();
    void setLED(int index, int r, int g, int b);
    void updateRainbow();

private:
    CRGB leds[NUM_LEDS];
    int hue = 0;
};

#endif
