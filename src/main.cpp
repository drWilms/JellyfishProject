#include <FastLED.h>
#include "TimerManager.h"

#define NUM_LEDS 10
#define DATA_PIN 4

CRGB leds[NUM_LEDS];

HighSpeedTimer highSpeed;
MidSpeedTimer midSpeed;
LowSpeedTimer lowSpeed;

void audioUpdate() {
    Serial.println("Audio Update Triggered");
}

void backgroundTask() {
    Serial.println("Background Task Running");
}

void ledEffect() {
    static uint8_t brightness = 0;
    static bool increasing = true;

    if (increasing) {
        brightness += 5;
        if (brightness >= 255) increasing = false;
    } else {
        brightness -= 5;
        if (brightness <= 0) increasing = true;
    }

    leds[0] = CRGB(brightness, 0, 0);
 
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    midSpeed.addTimer(100, audioUpdate);
    lowSpeed.addTimer(1000, backgroundTask);

    Serial.println("Timers Initialized");
}

void loop() {
    ledEffect();        // Run LED logic continuously
    highSpeed.update(); // Handles animations
    midSpeed.update();
    lowSpeed.update();
}
