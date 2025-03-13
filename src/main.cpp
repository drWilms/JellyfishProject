#include <Arduino.h>
#include "config.h"
#include "JellyfishQueue.h"
#include "HighSpeedTimer.h"
#include "MidSpeedTimer.h"
#include <FastLED.h>

#define DEBUG 1
#define LOG(x) if (DEBUG) Serial.println(F(x))

// LED Variables
CRGB leds[NUM_LEDS];
int brightness = 0;
bool fadeIn = true;

// Timer and Queue
JellyfishQueue eventQueue;
HighSpeedTimer highSpeedTimer;
MidSpeedTimer midSpeedTimer;

// Timer Intervals
const int PIN2_BLINK_ON = 222;
const int PIN2_BLINK_OFF = 888;

// === Reset LEDs Before Start ===
void resetLEDs() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}

// === LED Fade Effect (HighSpeedTimer) ===
void updateFadeEffect() {
    brightness += fadeIn ? 5 : -5;
    if (brightness >= 255) { brightness = 255; fadeIn = false; }
    if (brightness <= 0) { brightness = 0; fadeIn = true; }

    for (int i = 1; i < NUM_LEDS; i++) { // Explicitly turn off extra LEDs
        leds[i] = CRGB::Black;
    }

    leds[0] = CRGB(brightness, brightness, brightness);
    FastLED.show();
}

// === Blink Built-in LED (MidSpeedTimer) ===
bool ledState = false;
void togglePin2LED() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    
    // ✅ Ensure it enqueues itself properly
    eventQueue.enqueueDelayed(ledState ? PIN2_BLINK_ON : PIN2_BLINK_OFF, togglePin2LED);
}

void setup() {
    Serial.begin(115200);
    delay(500);
    LOG("=== ESP32 Booting ===");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS);
    resetLEDs();

    // ✅ Force timers to execute continuously
    highSpeedTimer.addTask(10, updateFadeEffect);
    midSpeedTimer.addTask(222, togglePin2LED);

    eventQueue.enqueueDelayed(500, togglePin2LED); // ✅ Ensure first LED toggle enqueues itself
    LOG("setup: All initializations completed");
    Serial.flush();
}

void loop() {
    eventQueue.processQueue();
    highSpeedTimer.update();
    midSpeedTimer.update();

    // ✅ Ensure FastLED updates every loop cycle
    FastLED.show();
}
