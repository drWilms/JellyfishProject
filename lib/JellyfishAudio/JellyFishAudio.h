#ifndef JELLYFISH_AUDIO_H
#define JELLYFISH_AUDIO_H

#include <Arduino.h>
#include <SD.h>
#include <AudioGeneratorMP3.h>
#include <AudioFileSourceSD.h>
#include <AudioOutputI2S.h>
#include "JellyfishLEDs.h"
#include "config.h"

// =========================
// Embedded AudioOutputI2SWithLevel Class
// =========================
class AudioOutputI2SWithLevel : public AudioOutputI2S {
public:
    AudioOutputI2SWithLevel() : audioLevel(0), currentGain(1.0f) {}

    virtual bool SetGain(float gain) override {
        currentGain = gain;
        return AudioOutputI2S::SetGain(gain);
    }

    float getCurrentGain() const {
        return currentGain;
    }

    virtual bool ConsumeSample(int16_t sample[2]) override {
        sample[0] = (int16_t)(sample[0] * currentGain);
        sample[1] = (int16_t)(sample[1] * currentGain);

        int16_t left = abs(sample[0]);
        int16_t right = abs(sample[1]);
        audioLevel = (left + right) / 2;

        return AudioOutputI2S::ConsumeSample(sample);
    }

    int getAudioLevel() {
        return audioLevel;
    }

private:
    int audioLevel;
    float currentGain;
};

// =========================
// JellyfishAudio Class
// =========================
struct PlaylistEntry {
    const char* filename;
    unsigned long startSec;
    unsigned long endSec;
};

class JellyfishAudio {
public:
    JellyfishAudio(uint8_t csPin, uint8_t bclkPin, uint8_t lrcPin, uint8_t doutPin, JellyfishLEDs* ledController);

    void begin();
    void loop();
    bool playFragment(const char* filename, unsigned long startSec, unsigned long endSec);
    void stop();
    int getAudioLevel();
    void setPlaylist(PlaylistEntry* list, size_t size);
    bool playNext();
    bool isPlaying();

private:
    uint8_t _csPin, _bclkPin, _lrcPin, _doutPin;
    AudioFileSourceSD* file;
    AudioGeneratorMP3* mp3;
    AudioOutputI2SWithLevel* audioOutput;

    unsigned long fragmentStartTime, fragmentDuration;
    bool playingFragment;
    JellyfishLEDs* leds;
    PlaylistEntry* playlist;
    size_t playlistSize;
    size_t currentTrack;
    bool isFadingOut;
};

#endif // JELLYFISH_AUDIO_H
