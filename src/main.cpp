#include <Arduino.h>
#include "config.h"
#include <SD.h>
#include <SPI.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <FastLED.h>
#include "JellyfishAudio.h"
#include "JellyfishQueue.h"
#include "JellyfishLEDs.h"
#include "TimerManager.h"

// ======= LED Configuratie =======
CRGBArray<NUM_LEDS> leds;

// ======= Objecten =======
JellyfishAudio* jellyfishAudio;
JellyfishLEDs* jellyfishLEDs;
JellyfishQueue queueManager;
TimerManager timerManager;

// ✅ MP3 bestand definitie hersteld
#define MP3_FILE "/test.mp3" 

// === LED Update Timer Callback ===
void updateLEDsTask() {
    int level = jellyfishAudio->getAudioLevel(); // ✅ Correcte aanroep
    int brightness = map(level, 0, 5000, 10, 255);
    brightness = constrain(brightness, 10, 255);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(160, 255, brightness);
    }
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    delay(3000); // Wacht op hardware/Serial

    jellyfishLEDs = new JellyfishLEDs();
    jellyfishAudio = new JellyfishAudio(PIN_SD_CS, PIN_I2S_BCLK, PIN_I2S_LRC, PIN_I2S_DOUT, jellyfishLEDs);
    jellyfishAudio->begin();

    // ✅ LED-initialisatie met `config.h` waarden
    FastLED.addLeds<LED_TYPE, PIN_RGB, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MAX_MILLIAMPS);
    FastLED.clear();
    FastLED.show();

    // ✅ Start MP3-fragment van 5s tot 15s
    jellyfishAudio->playFragment(MP3_FILE, 5, 15);

    // ✅ TimerManager gebruiken voor LED updates elke 50ms
    timerManager.addTimer(50, updateLEDsTask);
}

void loop() {
    timerManager.update();
    queueManager.process();
    jellyfishAudio->loop();
}
