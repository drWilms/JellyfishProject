#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "SWTimer.h"
#include "SWTimerManager.h"

SWTimerManager timerManager;

// LED Arrays
CRGB leds[NUM_LEDS];

// SWTimers for LED effects
SWTimer onBoardLEDTimer(LED_BLINK_INTERVAL);
SWTimer rgbBlinkTimer(750);  // Blinking blue every 750ms
SWTimer rainbowTimer(50);    // Slow rainbow effect update

// Function to toggle on-board LED
void toggleOnBoardLED() {
    static bool ledState = false;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    ledState = !ledState;
}

// Function to toggle RGB LED #0 to blue
void toggleRGBBlue() {
    static bool isOn = false;
    leds[0] = isOn ? CRGB::Black : CRGB::Blue;
    isOn = !isOn;
    FastLED.show();
}

// Function to update the rainbow effect
void updateRainbow() {
    static uint8_t hue = 0;
    for (int i = 1; i < NUM_LEDS; i++) {  // Start from LED 1 to leave LED 0 for blinking
        leds[i] = CHSV(hue + (i * 10), 255, 150);
    }
    hue += 1;  // Shift the colors over time
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();
    FastLED.show();

    // Start timers
    onBoardLEDTimer.start();
    rgbBlinkTimer.start();
    rainbowTimer.start();

    Serial.println("🚀 Jellyfish Project: LED Animation Start");
}

void loop() {
    // Handle on-board LED blink
    if (onBoardLEDTimer.isReady()) {
        toggleOnBoardLED();
        onBoardLEDTimer.start();  // Restart timer
    }

    // Handle RGB LED #0 blinking blue
    if (rgbBlinkTimer.isReady()) {
        toggleRGBBlue();
        rgbBlinkTimer.start();  // Restart timer
    }

    // Handle rainbow effect
    if (rainbowTimer.isReady()) {
        updateRainbow();
        rainbowTimer.start();  // Restart timer
    }
}
