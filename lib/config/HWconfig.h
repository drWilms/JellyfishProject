
 #ifndef HWCONFIG_H
 #define HWCONFIG_H
 
 #include <Arduino.h>
 #include "config_secrets.h"
 
 // ======================= Pin Definitions =======================
 #define LED_PIN        2   // Built-in LED
 #define PIN_RGB        4   // LED Data Out
 #define PIN_I2S_DOUT   14  // I2S Data
 #define PIN_I2S_BCLK   13  // I2S Bit Clock
 #define PIN_I2S_LRC    15  // I2S Left/Right Clock
 #define PIN_SD_CS      5   // SD Card Chip Select
 
 // SPI/I2C Pins
 #define SDA           21
 #define SCL           22
 #define SD_CS          5
 #define SPI_MOSI      23
 #define SPI_MISO      19
 #define SPI_SCK       18
 
 // ======================= LED Configuration =======================
 #define NUM_LEDS      10      // Number of LEDs
 #define LED_TYPE      WS2812   // LED Type
 #define LED_RGB_ORDER GRB      // RGB Order
 

 
 #endif  // HWCONFIG_H
 