#ifndef JELLYFISH_AUDIO_H
#define JELLYFISH_AUDIO_H

#include <Arduino.h>
#include <SD.h>
#include <AudioGeneratorMP3.h>
#include <AudioFileSourceSD.h>
#include "AudioOutputI2SWithLevel.h"
#include "JellyfishLEDs.h"
#include "Debug.h"
#include "config.h"

// Playlist structure
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
    // Audio Configuration
    uint8_t _csPin, _bclkPin, _lrcPin, _doutPin;
    AudioFileSourceSD* file;
    AudioGeneratorMP3* mp3;
    AudioOutputI2SWithLevel* audioOutput;

    // Fragment and Playlist Management
    unsigned long fragmentStartTime, fragmentDuration;
    bool playingFragment;
    JellyfishLEDs* leds;
    PlaylistEntry* playlist;
    size_t playlistSize;
    size_t currentTrack;
    bool isFadingOut;
};

#endif
