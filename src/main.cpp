#include <Arduino.h>
#include "config.h"
#include "TimerManager.h"
#include "JellyfishQueue.h"
#include <FastLED.h>

HighSpeedTimer highSpeed;
MidSpeedTimer midSpeed;
LowSpeedTimer lowSpeed;

JellyfishQueue fastPrintQueue;  // Stores ':' and ';'
JellyfishQueue midPrintQueue;   // Stores '*' and '#'
JellyfishQueue slowPrintQueue;  // Stores '=' and '-'

CRGB leds[NUM_LEDS];

// === Fast Print Pattern (Queue Fill) ===
const char fastCycleChars[] = {':', ';'};
int fastPattern[] = {6, 1, 6, 2, 5, 3};  // Spacing Pattern
int fastPatternIndex = 0;

// === Mid Print Pattern (Queue Fill) ===
const char midCycleChars[] = {'*', '#'};
int midPatternIndex = 0;

// === Slow Print Pattern (Queue Fill) ===
const char slowCycleChars[] = {'=', '-'};
int slowPatternIndex = 0;

// === LED Fade Variables ===
struct LEDFade {
    int fadeValue;
    bool fadeUp;
    uint8_t r, g, b;
    int step;
};

LEDFade ledFades[NUM_LEDS];  // Array for independent LED fades

// === Fill Fast Print Queue (": and ;") ===
void fillFastPrintQueue() {
    if (fastPrintQueue.isEmpty()) {
        if (fastPatternIndex < sizeof(fastPattern) / sizeof(fastPattern[0])) {
            char currentChar = fastCycleChars[fastPatternIndex % 2];
            int count = fastPattern[fastPatternIndex];

            for (int i = 0; i < count; i++) {
                fastPrintQueue.add(currentChar);
            }
            fastPatternIndex = (fastPatternIndex + 1) % (sizeof(fastPattern) / sizeof(fastPattern[0]));
        }
    }
}

// === Fill Mid Print Queue ("* and #") ===
void fillMidPrintQueue() {
    if (midPrintQueue.isEmpty()) {
        midPrintQueue.add(midCycleChars[midPatternIndex % 2]);
        midPrintQueue.add('\n');  // Ensure line break
        midPatternIndex++;
    }
}

// === Fill Slow Print Queue ("= and -") ===
void fillSlowPrintQueue() {
    if (slowPrintQueue.isEmpty()) {
        slowPrintQueue.add(slowCycleChars[slowPatternIndex % 2]);
        slowPrintQueue.add('\n');  // Ensure line break
        slowPatternIndex++;
    }
}

// === Print from Fast Queue (Every 1s) ===
void processFastPrintQueue() {
    if (!fastPrintQueue.isEmpty()) {
        Serial.print(fastPrintQueue.dequeue());
    }
    fillFastPrintQueue(); // Refill if empty
}

// === Print from Mid Queue (Every 17s) ===
void processMidPrintQueue() {
    if (!midPrintQueue.isEmpty()) {
        Serial.print(midPrintQueue.dequeue());
    }
    fillMidPrintQueue(); // Refill if empty
}

// === Print from Slow Queue (Every 19s) ===
void processSlowPrintQueue() {
    if (!slowPrintQueue.isEmpty()) {
        Serial.print(slowPrintQueue.dequeue());
    }
    fillSlowPrintQueue(); // Refill if empty
}

// === LED Blink (PIN 2, 20ms OFF / 17ms ON) ===
void blinkLED() {
    static bool ledState = false;
    digitalWrite(LED_PIN, ledState);
    ledState = !ledState;
}

// === RGB LED Fade (ALL LEDs Different) ===
void fadeRGB() {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (ledFades[i].fadeUp) {
            ledFades[i].fadeValue += ledFades[i].step;
            if (ledFades[i].fadeValue >= 255) {
                ledFades[i].fadeValue = 255;
                ledFades[i].fadeUp = false;
            }
        } else {
            ledFades[i].fadeValue -= ledFades[i].step;
            if (ledFades[i].fadeValue <= 0) {
                ledFades[i].fadeValue = 0;
                ledFades[i].fadeUp = true;
            }
        }

        leds[i] = CRGB(
            (ledFades[i].r * ledFades[i].fadeValue) / 255,
            (ledFades[i].g * ledFades[i].fadeValue) / 255,
            (ledFades[i].b * ledFades[i].fadeValue) / 255
        );
    }
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    FastLED.addLeds<LED_TYPE, PIN_LED, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    // Initialize LED Fades
    for (int i = 0; i < NUM_LEDS; i++) {
        ledFades[i].fadeValue = random(50, 200);
        ledFades[i].fadeUp = random(0, 2);
        ledFades[i].r = random(50, 255);
        ledFades[i].g = random(50, 255);
        ledFades[i].b = random(50, 255);
        ledFades[i].step = random(3, 10);  // Different speeds
    }

    // === Add Timers (All Firing Independently) ===
    highSpeed.addTimer(20, blinkLED);          // LED Blinking (20ms OFF, 17ms ON)
    highSpeed.addTimer(50, fadeRGB);           // RGB LED Fading
    midSpeed.addTimer(1000, processFastPrintQueue);  // Print from fast queue (1s)
    lowSpeed.addTimer(17000, processMidPrintQueue);  // Print from mid queue (17s)
    lowSpeed.addTimer(19000, processSlowPrintQueue); // Print from slow queue (19s)

    // === Fill Queues Initially ===
    fillFastPrintQueue();
    fillMidPrintQueue();
    fillSlowPrintQueue();
}

void loop() {
    highSpeed.update();
    midSpeed.update();
    lowSpeed.update();
}
