# JellyfishAudio Library

## Overview
JellyfishAudio is responsible for managing audio playback in the Jellyfish project. It supports MP3 playback, audio level extraction, and seamless integration with the timer and queue systems.

## Features
- MP3 playback from SD card
- Supports audio level extraction for LED synchronization
- Fade-in and fade-out effects for smooth transitions
- Playlist support with configurable start and stop times
- Designed to work with external I2S DAC

## Installation
Place `JellyfishAudio.h` and `JellyfishAudio.cpp` inside the `lib/JellyfishAudio` directory of your PlatformIO project.

## Usage Example
```cpp
#include "JellyfishAudio.h"

JellyfishAudio audio;

audio.playTrack("/track1.mp3", 10, 20);
if (audio.isPlaying()) {
    int level = audio.getAudioLevel();
}
