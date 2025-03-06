#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// === Pin Definitions ===
#define LED_PIN        2  // Built-in LED
#define PIN_LED        4  // LED Data Out
#define PIN_I2S_DOUT  14  // I2S Data
#define PIN_I2S_BCLK  13  // I2S Bit Clock
#define PIN_I2S_LRC   15  // I2S Left/Right Clock
#define PIN_SD_CS      5  // SD Card Chip Select

// === LED Configuration ===
#define NUM_LEDS 10
#define LED_TYPE WS2812    // Define LED type
#define LED_RGB_ORDER GRB  // Define RGB order

// === Timer Intervals ===
#define LED_TIMER_INTERVAL 500   // LED update interval in milliseconds
#define LED_BLINK_INTERVAL 1000  // 1-second blink for on-board LED
#define EVENT_PROCESS_INTERVAL 2000  // Queue processing interval in ms
#define LED_EFFECT_DURATION 3000  // Default LED effect duration in ms

// === Default LED Settings ===
#define DEFAULT_BRIGHTNESS 150  // Default LED brightness level

// === Global Variables ===
extern int audioLevel;   // Stores real-time audio level
extern bool silentMode;  // True if LEDs should remain off
extern int brightness;   // LED brightness level

#endif  // CONFIG_H
