/**
 * Jellyfish Project - Fully Restored Codebase with Timer Hierarchy
 * Version: 2025-03-07
 */

// ========================= config.h =========================
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "config_secrets.h"

// === Pin Definitions ===
#define LED_PIN         2  // Built-in LED
#define PIN_RGB         4  // LED Data Out
#define PIN_LED         PIN_RGB
#define PIN_I2S_DOUT   14  // I2S Data
#define PIN_I2S_BCLK   13  // I2S Bit Clock
#define PIN_I2S_LRC    15  // I2S Left/Right Clock
#define PIN_SD_CS       5  // SD Card Chip Select

// === LED Configuration ===
#define NUM_LEDS 10
#define LED_TYPE WS2812    // Define LED type
#define LED_RGB_ORDER GRB  // Define RGB order

#define MAX_MILLIAMPS 2000
#define VOLTAGE 5

// === Timer Intervals ===
//#define SLOW_TIMER_INTERVAL   1000  // 1 second and above
//#define FAST_TIMER_INTERVAL    250  // 100ms - 999ms
//#define ULTRAFAST_TIMER_INTERVAL 50 // Below 100ms

// === Global Variables ===
extern int audioLevel;   // Stores real-time audio level
extern bool silentMode;  // True if LEDs should remain off
extern int brightness;   // LED brightness level



#define SDA           21
#define SCL           22
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18



#endif  // CONFIG_H