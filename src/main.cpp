#include <Arduino.h>
#include "config.h"
#include "macros.inc"
#include "SWTimer.h"
#include "SWTimerManager.h"
#include <FastLED.h>

CRGB leds[NUM_LEDS];

// === Interval Definitions ===
#define LED_ONBOARD_BLINK_INTERVAL 1000  // On-board LED blinks every second
#define LED_FADE_INTERVAL 50        // RGB LED 0 fades every 50ms
#define LED_BLINK_FAST_INTERVAL 100 // RGB LED 1 blinks fast every 100ms
#define LED_COLOR_CHANGE_INTERVAL 300 // RGB LED 2 changes color after 3 blinks

// Timers for individual LED behaviors
SWTimerManager timerManager;
int onboardLedTimerID, fadeLedTimerID, blinkFastLedTimerID, colorChangeLedTimerID;

// Variables for LED states
bool onboardLedState = false;
int fadeBrightness = 0;
bool fadeUp = true;
bool blinkFastState = false;
int blinkCount = 0;
CRGB colors[] = {CRGB::Red, CRGB::Yellow, CRGB::Blue};
int colorIndex = 0;

void setup() {
    Serial.begin(115200);
    LOG("🚀 Jellyfish Project: Individual LED Timing");

    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Start timers for LED effects
    onboardLedTimerID = timerManager.addTimer(LED_ONBOARD_BLINK_INTERVAL);  // On-board LED
    fadeLedTimerID = timerManager.addTimer(LED_FADE_INTERVAL);    // RGB LED 0
    blinkFastLedTimerID = timerManager.addTimer(LED_BLINK_FAST_INTERVAL);  // RGB LED 1
    colorChangeLedTimerID = timerManager.addTimer(LED_COLOR_CHANGE_INTERVAL);  // RGB LED 2

    timerManager.startTimer(onboardLedTimerID);
    timerManager.startTimer(fadeLedTimerID);
    timerManager.startTimer(blinkFastLedTimerID);
    timerManager.startTimer(colorChangeLedTimerID);

    LOG("✅ Individual LED Timers Initialized");
}

void loop() {
    // On-board LED (PIN 2) - Simple 1-second blinking
    if (timerManager.isReady(onboardLedTimerID)) {
        onboardLedState = !onboardLedState;
        digitalWrite(LED_PIN, onboardLedState ? HIGH : LOW);
    }

    // RGB LED 0 - Fading effect
    if (timerManager.isReady(fadeLedTimerID)) {
        fadeBrightness += (fadeUp ? 5 : -5);
        if (fadeBrightness >= 255) { fadeUp = false; }
        if (fadeBrightness <= 0) { fadeUp = true; }
        leds[0] = CHSV(0, 255, fadeBrightness);  // Red fading
        FastLED.show();
    }

    // RGB LED 1 - Fast blinking
    if (timerManager.isReady(blinkFastLedTimerID)) {
        blinkFastState = !blinkFastState;
        leds[1] = blinkFastState ? CRGB::Green : CRGB::Black;
        FastLED.show();
    }

    // RGB LED 2 - Change color after 3 blinks
    if (timerManager.isReady(colorChangeLedTimerID)) {
        blinkCount++;
        if (blinkCount >= 3) {
            colorIndex = (colorIndex + 1) % 3;
            leds[2] = colors[colorIndex];
            blinkCount = 0;
            FastLED.show();
        }
    }

    // ✅ Use non-blocking delay
    WAIT(10);
}
