/**
 * @file AudioManager.h
 * @brief Manages audio playback and volume fading for Jellyfish Project
 * @author Jan Wilms
 * @date 2025-03-16 17:45 (Amsterdam Time)
 */

 #ifndef AUDIO_MANAGER_H
 #define AUDIO_MANAGER_H
 
 #include <Arduino.h>
 #include <SD.h>
 #include <AudioGeneratorMP3.h>
 #include <AudioFileSourceSD.h>
 #include <AudioOutputI2S.h>
 #include "LightManager.h"
 #include "HWconfig.h"
 
 struct PlaylistEntry {
     const char* filename;
     unsigned long startSec;
     unsigned long endSec;
 };
 
 class AudioManager {
 public:
     AudioManager(uint8_t csPin, uint8_t bclkPin, uint8_t lrcPin, uint8_t doutPin, LightManager* lightManager);
 
     void begin();
     void loop();
     bool playFragment(const char* filename, unsigned long startSec, unsigned long endSec);
     void stop();
     int getAudioLevel();
     void setPlaylist(PlaylistEntry* list, size_t size);
     bool playNext();
     bool isPlaying();
     void setVolume(float volume);  // 🔹 Added setter for volume control
 
 private:
     class AudioOutputI2SWithLevel;
 
     uint8_t _csPin, _bclkPin, _lrcPin, _doutPin;
     AudioFileSourceSD* file;
     AudioGeneratorMP3* mp3;
     AudioOutputI2SWithLevel* audioOutput;
 
     unsigned long fragmentStartTime, fragmentDuration;
     bool playingFragment;
     LightManager* lightManager;
     PlaylistEntry* playlist;
     size_t playlistSize;
     size_t currentTrack;
     bool isFadingOut;
 
     // 🔹 FreeRTOS Tasks for Fade In/Out
     static void Task_AudioFadeIn(void* pvParameters);
     static void Task_AudioFadeOut(void* pvParameters);
 };
 
 #endif // AUDIO_MANAGER_H
 