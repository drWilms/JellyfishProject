#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// === Pin Definitions ===
#define PIN_LED        4  // LED Data Out
#define PIN_I2S_DOUT  14  // I2S Data
#define PIN_I2S_BCLK  13  // I2S Bit Clock
#define PIN_I2S_LRC   15  // I2S Left/Right Clock
#define PIN_SD_CS      5  // SD Card Chip Select

// === Global Variables ===
extern int audioLevel;   // Stores real-time audio level
extern bool silentMode;  // True if LEDs should remain off
extern int brightness;   // LED brightness level

#ifdef __cplusplus
}
#endif

#endif  // CONFIG_H
