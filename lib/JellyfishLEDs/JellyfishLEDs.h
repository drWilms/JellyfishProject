#ifndef JELLYFISHLEDS_H
#define JELLYFISHLEDS_H

#include <Arduino.h>
#include "config.h"      // NUM_LEDS must be included BEFORE it's used
#include <FastLED.h>
#include "SWTimerManager.h"

class JellyfishLEDs {
private:
    CRGB* leds;          // Use pointer instead of fixed array
    SWTimerManager* timerManager;
    int timerID;

public:
    JellyfishLEDs(SWTimerManager* tm);
    ~JellyfishLEDs();    // Destructor to free memory
    void begin();
    void update();
};

#endif  // JELLYFISHLEDS_H
