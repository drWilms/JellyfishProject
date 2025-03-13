#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <FastLED.h>
#include "AudioOutputI2SWithLevel.h"
#include "JellyfishQueue.h"
#include "config.h"

// ======= Versie & Timestamp =======
#define JELLYFISH_VERSION "Demo6"
#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

// ======= MP3-bestand =======
#define MP3_FILE "/test.mp3"  // Gedefinieerd in main.cpp (geen hardware)

// ======= LED Configuration =======
CRGB leds[NUM_LEDS];  // Correcte LED-array declaratie

// ======= Audio Objects =======
AudioFileSourceSD *file;
AudioGeneratorMP3 *mp3;
AudioOutputI2SWithLevel *audioOutput;

// Playback Control
bool playingFragment = false;
unsigned long fragmentStartTime = 0;
unsigned long fragmentDuration = 0;

// Queue
JellyfishQueue queue;

// ======= Queue Event Types =======
enum QueueEventType {
    PLAY_MP3_FRAGMENT,
    FADE_IN,
    FADE_OUT,
    UPDATE_LEDS
};

// ======= MP3 Playback Function =======
bool playFragmentMP3(const char* filename, unsigned long startSec, unsigned long endSec) {
  if (mp3 && mp3->isRunning()) {
      mp3->stop();
  }
  if (file) {
      file->close();
      delete file;
      file = nullptr;
  }

  file = new AudioFileSourceSD(filename);
  const unsigned long bytesPerSec = 16000;
  unsigned long startOffset = startSec * bytesPerSec;

  if (!file->seek(startOffset, SEEK_SET)) {
      Serial.println("Seek failed!");
      return false;
  }

  if (!mp3->begin(file, audioOutput)) {
      Serial.println("MP3 playback failed to start!");
      return false;
  }

  fragmentDuration = (endSec - startSec) * 1000;
  fragmentStartTime = millis();
  playingFragment = true;

  Serial.printf("Playing fragment from %lu s to %lu s\n", startSec, endSec);
  return true;
}


// ======= LED Update Function =======
void updateLEDs() {
    int level = audioOutput->getAudioLevel();
    Serial.printf("Audio Level: %d\n", level);
//    int brightness = map(level, 0, 5000, 10, 255);
brightness = 100;  // Test of alle LEDs goed reageren

    brightness = constrain(brightness, 10, 255);
    
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(160, 255, brightness);
    }
    Serial.print("LED Levels: ");
for (int i = 0; i < NUM_LEDS; i++) {
    Serial.printf("[%d]=%d ", i, leds[i].getLuma());
}
Serial.println();

    FastLED.show();
}

void processQueue() {
  if (queue.isEmpty()) return;
  QueueEventType event = (QueueEventType)queue.dequeue();  // Correcte queue-methode

  switch (event) {
      case PLAY_MP3_FRAGMENT:
          playFragmentMP3(MP3_FILE, 5, 15);  // Correcte aanroep
          break;
      case FADE_IN:
          Serial.println("Executing FADE-IN event.");
          break;
      case FADE_OUT:
          Serial.println("Executing FADE-OUT event.");
          break;
      case UPDATE_LEDS:
          updateLEDs();
          break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.printf("Starting %s - Compiled on %s at %s\n", JELLYFISH_VERSION, COMPILE_DATE, COMPILE_TIME);

  if (!SD.begin(SD_CS)) {
      Serial.println("SD Card Mount Failed!");
      while (1);
  }
  Serial.println("SD Card Mounted!");

  file = new AudioFileSourceSD(MP3_FILE);
  mp3 = new AudioGeneratorMP3();
 // audioOutput = new AudioOutputI2SWithLevel();
 AudioOutputI2S* audioOutput = new AudioOutputI2S();


  audioOutput->SetPinout(PIN_I2S_BCLK, PIN_I2S_LRC, PIN_I2S_DOUT);
  audioOutput->SetOutputModeMono(false);
  audioOutput->SetRate(44100);
  audioOutput->SetGain(1.0);

  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);  // Correcte voltagewaarde
  FastLED.clear();
  FastLED.show();

  // **MP3 Fragment Playback via Queue**
  queue.add(PLAY_MP3_FRAGMENT);
}

// ======= Main Loop =======
void loop() {
    processQueue();
    int level = audioOutput->getAudioLevel();
 //   Serial.printf("Audio Level Test: %d\n", level);

}
