# JellyfishLEDs Library

## Overview
JellyfishLEDs is responsible for controlling LED animations and effects in the Jellyfish project. It provides smooth lighting transitions, audio-reactive effects, and integrates with the project's timer and queue system.

## Features
- Supports individually addressable LEDs (FastLED)
- Multiple animation modes (breathing, pulsing, color waves, etc.)
- Audio-reactive lighting effects
- Integration with Jellyfish's tiered timer system
- Configurable brightness and color palettes

## Installation
Place `JellyfishLEDs.h` and `JellyfishLEDs.cpp` inside the `lib/JellyfishLEDs` directory of your PlatformIO project.

## Usage Example
```cpp
#include "JellyfishLEDs.h"

JellyfishLEDs leds;

leds.setBrightness(150);
leds.setColor(0, CRGB::Blue);
leds.startBreathingEffect();
