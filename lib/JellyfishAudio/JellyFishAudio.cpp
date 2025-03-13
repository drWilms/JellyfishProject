/* ==========================
   File: lib/JellyfishAudio/JellyfishAudio.cpp
   ========================== */
   #include "JellyfishAudio.h"

   JellyfishAudio::JellyfishAudio(uint8_t csPin, uint8_t bclkPin, uint8_t lrcPin, uint8_t doutPin, JellyfishLEDs* ledController)
       : _csPin(csPin), _bclkPin(bclkPin), _lrcPin(lrcPin), _doutPin(doutPin),
         file(nullptr), mp3(nullptr), audioOutput(nullptr),
         fragmentStartTime(0), fragmentDuration(0), playingFragment(false), leds(ledController),
         playlist(nullptr), playlistSize(0), currentTrack(0), isFadingOut(false) {}
   
   void JellyfishAudio::begin() {
       if (!SD.begin(_csPin)) {
           Serial.println("SD Card Mount Failed!");
           while (1);
       }
       Serial.println("SD Card Mounted!");
   
       audioOutput = new AudioOutputI2SWithLevel();
       audioOutput->SetPinout(_bclkPin, _lrcPin, _doutPin);
       audioOutput->SetOutputModeMono(false);
       audioOutput->SetRate(44100);
       audioOutput->SetGain(1.0);
   
       mp3 = new AudioGeneratorMP3();
   }
   
   bool JellyfishAudio::playFragment(const char* filename, unsigned long startSec, unsigned long endSec) {
       stop();
   
       file = new AudioFileSourceSD(filename);
       if (!file) {
           Serial.printf("Failed to open file: %s\n", filename);
           return false;
       }
   
       const unsigned long bytesPerSec = 16000;
       unsigned long startOffset = startSec * bytesPerSec;
       file->seek(startOffset, SEEK_SET);
   
       if (!mp3->begin(file, audioOutput)) {
           Serial.println("MP3 playback failed to start!");
           return false;
       }
   
       fragmentDuration = (endSec - startSec) * 1000;
       fragmentStartTime = millis();
       playingFragment = true;
       isFadingOut = false;
   
       Serial.printf("Playing fragment from %lu s to %lu s\n", startSec, endSec);
   
       audioOutput->SetGain(0);
       return true;
   }
   
   void JellyfishAudio::loop() {
       if (playingFragment && mp3 && mp3->isRunning()) {
           mp3->loop();
           unsigned long elapsedTime = millis() - fragmentStartTime;
   
           if (elapsedTime < 3000) {
               float gain = (float)elapsedTime / 3000.0;
               audioOutput->SetGain(gain);
           }
           else if (fragmentDuration - elapsedTime < 3000) {
               float gain = (float)(fragmentDuration - elapsedTime) / 3000.0;
               audioOutput->SetGain(gain);
               isFadingOut = true;
           }
           else {
               audioOutput->SetGain(1.0);
           }
       } else if (playingFragment) {
           Serial.println("Fragment finished. Moving to next track...");
           playingFragment = false;
           playNext();
       }
   }
   
   void JellyfishAudio::stop() {
       if (mp3 && mp3->isRunning()) {
           mp3->stop();
       }
       playingFragment = false;
   }
   
   int JellyfishAudio::getAudioLevel() {
       return audioOutput ? audioOutput->getAudioLevel() : 0;
   }
   
   void JellyfishAudio::setPlaylist(PlaylistEntry* list, size_t size) {
       playlist = list;
       playlistSize = size;
       currentTrack = 0;
   }
   
   bool JellyfishAudio::playNext() {
       if (currentTrack >= playlistSize) {
           Serial.println("End of playlist reached. Stopping playback.");
           currentTrack = 0;
           playingFragment = false;
           audioOutput->stop();
           leds->silentMode();
           return false;
       }
   
       PlaylistEntry entry = playlist[currentTrack];
       currentTrack++;
   
       return playFragment(entry.filename, entry.startSec, entry.endSec);
   }
   
   bool JellyfishAudio::isPlaying() {
       return playingFragment;
   }
   