/**
 * @file AudioManager.cpp
 * @brief Implements MP3 playback with audio fading for Jellyfish Project
 * @author Jan Wilms
 * @date 2025-03-16 17:45 (Amsterdam Time)
 */

 #include "AudioManager.h"

 class AudioManager::AudioOutputI2SWithLevel : public AudioOutputI2S {
 public:
     AudioOutputI2SWithLevel() : audioLevel(0), currentGain(1.0f) {}
 
     bool SetGain(float gain) override {
         currentGain = gain;
         return AudioOutputI2S::SetGain(gain);
     }
 
     float getCurrentGain() const { return currentGain; }
 
     bool ConsumeSample(int16_t sample[2]) override {
         sample[0] = (int16_t)(sample[0] * currentGain);
         sample[1] = (int16_t)(sample[1] * currentGain);
         audioLevel = (abs(sample[0]) + abs(sample[1])) / 2;
         return AudioOutputI2S::ConsumeSample(sample);
     }
 
     int getAudioLevel() { return audioLevel; }
 
 private:
     int audioLevel;
     float currentGain;
 };
 
 AudioManager::AudioManager(uint8_t csPin, uint8_t bclkPin, uint8_t lrcPin, uint8_t doutPin, LightManager* lightManager)
     : _csPin(csPin), _bclkPin(bclkPin), _lrcPin(lrcPin), _doutPin(doutPin),
       file(nullptr), mp3(nullptr), audioOutput(nullptr),
       fragmentStartTime(0), fragmentDuration(0), playingFragment(false),
       lightManager(lightManager), playlist(nullptr), playlistSize(0), currentTrack(0), isFadingOut(false) {}
 
 void AudioManager::begin() {
     if (!SD.begin(_csPin)) {
         Serial.println("[ERROR] SD Card Mount Failed!");
         while (1);
     }
     Serial.println("[INFO] SD Card Mounted!");
 
     audioOutput = new AudioOutputI2SWithLevel();
     audioOutput->SetPinout(_bclkPin, _lrcPin, _doutPin);
     audioOutput->SetOutputModeMono(false);
     audioOutput->SetRate(44100);
     audioOutput->SetGain(0.0f);  // Start with zero volume
 
     mp3 = new AudioGeneratorMP3();
 }
 
 void AudioManager::setVolume(float volume) {
     if (audioOutput) {
         audioOutput->SetGain(volume);
     }
 }
 
 bool AudioManager::playFragment(const char* filename, unsigned long startSec, unsigned long endSec) {
     stop();
 
     file = new AudioFileSourceSD(filename);
     if (!file) {
         Serial.printf("[ERROR] Failed to open file: %s\n", filename);
         return false;
     }
 
     const unsigned long bytesPerSec = 16000;
     unsigned long startOffset = startSec * bytesPerSec;
     file->seek(startOffset, SEEK_SET);
 
     if (!mp3->begin(file, audioOutput)) {
         Serial.println("[ERROR] MP3 playback failed to start!");
         return false;
     }
 
     fragmentDuration = (endSec - startSec) * 1000;
     fragmentStartTime = millis();
     playingFragment = true;
     isFadingOut = false;
 
     Serial.printf("[INFO] Playing fragment from %lu s to %lu s\n", startSec, endSec);
 
     // 🔹 Create FreeRTOS Fade In Task
     xTaskCreatePinnedToCore(Task_AudioFadeIn, "AudioFadeIn", 2048, this, 2, NULL, 1);
     return true;
 }
 
 // 🔹 FreeRTOS Fade-In Task
 void AudioManager::Task_AudioFadeIn(void *pvParameters) {
     AudioManager* self = static_cast<AudioManager*>(pvParameters);
     for (float volume = 0.0f; volume <= MAX_AUDIO_VOLUME; volume += 0.01f) {
         self->setVolume(volume);
         vTaskDelay(pdMS_TO_TICKS(50));
     }
     vTaskDelete(NULL);
 }
 
 // 🔹 FreeRTOS Fade-Out Task
 void AudioManager::Task_AudioFadeOut(void *pvParameters) {
     AudioManager* self = static_cast<AudioManager*>(pvParameters);
     for (float volume = MAX_AUDIO_VOLUME; volume >= 0.0f; volume -= 0.01f) {
         self->setVolume(volume);
         vTaskDelay(pdMS_TO_TICKS(50));
     }
     self->stop();
     vTaskDelete(NULL);
 }
 
 void AudioManager::loop() {
     if (playingFragment && mp3 && mp3->isRunning()) {
         mp3->loop();
         unsigned long elapsedTime = millis() - fragmentStartTime;
 
         if (elapsedTime >= fragmentDuration - 3000 && !isFadingOut) {
             isFadingOut = true;
             xTaskCreatePinnedToCore(Task_AudioFadeOut, "AudioFadeOut", 2048, this, 2, NULL, 1);
         }
     } else if (playingFragment) {
         Serial.println("[INFO] Fragment finished.");
         playingFragment = false;
     }
 }
 
 void AudioManager::stop() {
     if (mp3 && mp3->isRunning()) {
         mp3->stop();
     }
     playingFragment = false;
 }
 
 int AudioManager::getAudioLevel() {
     return audioOutput ? audioOutput->getAudioLevel() : 0;
 }
 
 void AudioManager::setPlaylist(PlaylistEntry* list, size_t size) {
     playlist = list;
     playlistSize = size;
     currentTrack = 0;
 }
 
 bool AudioManager::playNext() {
     if (currentTrack >= playlistSize) {
         Serial.println("[INFO] End of playlist reached.");
         currentTrack = 0;
         playingFragment = false;
         return false;
     }
 
     PlaylistEntry entry = playlist[currentTrack];
     currentTrack++;
 
     return playFragment(entry.filename, entry.startSec, entry.endSec);
 }
 
 bool AudioManager::isPlaying() {
     return playingFragment;
 }
 