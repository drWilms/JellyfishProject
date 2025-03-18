#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include <Arduino.h>
#include "FastLED.h"
#include "HWconfig.h"

class LightManager {
public:
    LightManager();
    void begin();
    void updateFadingEffect();
    void updateLight();

private:
    CRGB leds[NUM_LEDS];
    float brightnessFactor;
    uint32_t lastUpdateTime;
    const uint16_t fadeInterval = 10;
};

#endif
