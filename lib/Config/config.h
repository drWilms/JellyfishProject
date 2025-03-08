/**
 * Jellyfish Project - Refactored Codebase
 * Version: 2025-03-07
 */

// ========================= config.h =========================
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "config_secrets.h"

// === Pin Definitions ===
#define LED_PIN         2  // Built-in LED
#define PIN_LED         4  // LED Data Out
#define PIN_I2S_DOUT   14  // I2S Data
#define PIN_I2S_BCLK   13  // I2S Bit Clock
#define PIN_I2S_LRC    15  // I2S Left/Right Clock
#define PIN_SD_CS       5  // SD Card Chip Select

// === LED Configuration ===
#define NUM_LEDS 10
#define LED_TYPE WS2812    // Define LED type
#define LED_RGB_ORDER GRB  // Define RGB order

// === Timer Intervals ===
#define LED_TIMER_INTERVAL 500  // LED update interval in milliseconds
#define LED_BLINK_INTERVAL 1000 // 1-second blink for on-board LED
#define RGB_BLINK_INTERVAL 750  // Blinking interval for RGB LEDs
#define RAINBOW_INTERVAL 50     // Rainbow effect update interval

// === Global Variables ===
extern int audioLevel;   // Stores real-time audio level
extern bool silentMode;  // True if LEDs should remain off
extern int brightness;   // LED brightness level

#endif  // CONFIG_H
