// werkt OK: fragment, fadein en fadeuit, disco

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <FastLED.h>
#include "AudioOutputI2SWithLevel.h" // Custom class with gain & audio level

// ======= Pin Definitions =======
#define SD_CS 5
#define I2S_DOUT 14
#define I2S_BCLK 13
#define I2S_LRC 15
#define LED_PIN 4 // Data pin for LED strip

// ======= LED Configuration =======
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 21
#define MAX_MILLIAMPS 2000
#define VOLTAGE 5

CRGBArray<NUM_LEDS> leds;

// ======= Audio Configuration =======
#define BYTESPERSEC 16000
#define MP3_FILE "/test.mp3" // MP3 file on SD card root

// Global Audio Objects
AudioFileSourceSD *file;
AudioGeneratorMP3 *mp3;
AudioOutputI2SWithLevel *audioOutput;

// For fragment playback control
unsigned long fragmentStartTime = 0;
unsigned long fragmentDuration = 0; // in milliseconds
bool playingFragment = false;

// For LED updates (as before)
void updateLEDs()
{
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MAX_MILLIAMPS);
  int level = audioOutput->getAudioLevel();
  int brightness = map(level, 0, 5000, 10, 255);
  brightness = constrain(brightness, 10, 255);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(160, 255, brightness);
  }
  FastLED.show();
}

/**
 * Plays a fragment of the MP3 file.
 * @param filename The MP3 filename (with leading slash).
 * @param startSec The start time in seconds.
 * @param endSec   The end time in seconds.
 * @return true if playback started successfully.
 */
bool playFragmentMP3(const char *filename, unsigned long startSec, unsigned long endSec)
{
  // Stop current playback if any
  if (mp3 && mp3->isRunning())
  {
    mp3->stop();
  }
  if (file)
  {
    file->close();
    delete file;
    file = nullptr;
  }

  // Open the file
  file = new AudioFileSourceSD(filename);

  // For CBR MP3: calculate byte offset
  // Example: for 128 kbps, ~16,000 bytes per second.
  const unsigned long bytesPerSec = BYTESPERSEC;
  unsigned long startOffset = startSec * bytesPerSec;
  if (!file->seek(startOffset, SEEK_SET))
  {
    Serial.println("Seek failed!");
    return false;
  }

  // Restart the MP3 generator
  if (!mp3->begin(file, audioOutput))
  {
    Serial.println("MP3 playback failed to start!");
    return false;
  }

  // Calculate fragment duration in milliseconds
  fragmentDuration = (endSec - startSec) * 1000;
  fragmentStartTime = millis();
  playingFragment = true;

  Serial.printf("Playing fragment from %lu s to %lu s\n", startSec, endSec);
  return true;
}

void setup()
{
  Serial.begin(115200);
  delay(3000); // Allow hardware/Serial to initialize

  if (!SD.begin(SD_CS))
  {
    Serial.println("SD Card Mount Failed!");
    while (1)
      ;
  }
  Serial.println("SD Card Mounted!");

  // Initialize Audio Objects
  file = new AudioFileSourceSD(MP3_FILE);
  mp3 = new AudioGeneratorMP3();
  audioOutput = new AudioOutputI2SWithLevel();
  audioOutput->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audioOutput->SetOutputModeMono(false);
  audioOutput->SetRate(44100);
  audioOutput->SetGain(1.0); // Use full volume

  // Initialize LED strip
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MAX_MILLIAMPS);
  FastLED.clear();
  FastLED.show();

  // Start playing a fragment (for example, from 10 sec to 20 sec)
  playFragmentMP3(MP3_FILE, 5, 15);
}

void loop()
{
  // Continue decoding if playback is running
  if (playingFragment && mp3 && mp3->isRunning())
  {
    mp3->loop();
  }
  else if (playingFragment)
  {
    // Playback finished naturally, or stopped
    Serial.println("Fragment playback ended.");
    playingFragment = false;
  }

  // Check if fragment duration has elapsed
  if (playingFragment)
  {
    unsigned long elapsed = millis() - fragmentStartTime;
    // If we've played longer than our fragment, stop playback.
    if (elapsed >= fragmentDuration)
    {
      Serial.println("Fragment duration reached. Stopping playback.");
      mp3->stop();
      playingFragment = false;
    }
  }

  // Update LEDs continuously
  updateLEDs();
  delay(10);
}
