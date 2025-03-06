#include <Arduino.h>
#include <FastLED.h>
#include "SWTimer.h"
#include "SWTimerManager.h"
#include "config.h"
#include "macros.inc"

// LED Array
CRGB leds[NUM_LEDS];

// Timers
SWTimer onBoardLEDTimer(LED_BLINK_INTERVAL);
SWTimer rgbBlinkTimer(750);
SWTimer rgbSecondBlinkTimer(1000);
SWTimer rainbowTimer(50);

SWTimerManager timerManager;

// LED states
bool rgbBlinkState = false;
bool rgbSecondBlinkState = false;
bool onBoardLEDState = false;

// Toggle the onboard LED
void toggleOnBoardLED() {
    LOG("✅ Toggling Onboard LED");
    onBoardLEDState = !onBoardLEDState;
    digitalWrite(LED_PIN, onBoardLEDState);
}

// Blink `RGB #0`
void toggleRGBBlue() {
    LOG("✅ Toggling RGB #0 (Blue Blink)");
    rgbBlinkState = !rgbBlinkState;
    leds[0] = rgbBlinkState ? CRGB::Blue : CRGB::Black;
    FastLED.show();
}

// Blink `RGB #1` separately
void toggleRGBSecondLED() {
    LOG("✅ Toggling RGB #1 (Alternate Blink)");
    rgbSecondBlinkState = !rgbSecondBlinkState;
    leds[1] = rgbSecondBlinkState ? CRGB::Blue : CRGB::Black;
    FastLED.show();
}

// Update rainbow effect
void updateRainbow() {
    static uint8_t hue = 0;
    LOG("🌈 Updating Rainbow Effect");
    for (int i = 2; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, brightness);
    }
    FastLED.show();
    hue++;
}

// Setup
void setup() {
    Serial.begin(115200);
    FastLED.delay(1000);
   LOG("🚀 Jellyfish Project: LED Animation Start");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();
    FastLED.show();

    timerManager.addTimer(onBoardLEDTimer, toggleOnBoardLED);
    timerManager.addTimer(rgbBlinkTimer, toggleRGBBlue);
    timerManager.addTimer(rgbSecondBlinkTimer, toggleRGBSecondLED);
    timerManager.addTimer(rainbowTimer, updateRainbow);

    onBoardLEDTimer.start();
    rgbBlinkTimer.start();
    rgbSecondBlinkTimer.start();
    rainbowTimer.start();
}

// Main loop
void loop() {
    timerManager.update();
}
