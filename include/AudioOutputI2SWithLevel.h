#ifndef AUDIO_OUTPUT_I2S_WITH_LEVEL_H
#define AUDIO_OUTPUT_I2S_WITH_LEVEL_H

#include <AudioOutputI2S.h>

class AudioOutputI2SWithLevel : public AudioOutputI2S {
public:
    AudioOutputI2SWithLevel() : audioLevel(0), currentGain(1.0f) {}

    // Override SetGain to store the gain value and call the base class.
    virtual bool SetGain(float gain) override {
        currentGain = gain;
        return AudioOutputI2S::SetGain(gain);
    }

    // Getter for the current gain.
    float getCurrentGain() const {
        return currentGain;
    }
/*
    // Override ConsumeSample to apply the gain manually and compute the audio level.
    virtual bool ConsumeSample(int16_t sample[2]) override {
        // Apply the current gain to both channels.
        sample[0] = (int16_t)(sample[0] * currentGain);
        sample[1] = (int16_t)(sample[1] * currentGain);

        // Compute the audio level for LED updates.
        int16_t left = abs(sample[0]);
        int16_t right = abs(sample[1]);
        audioLevel = (left + right) / 2;

        Serial.printf("ConsumeSample: L=%d R=%d, Gain=%.2f, Level=%d\n", sample[0], sample[1], currentGain, audioLevel);

        return AudioOutputI2S::ConsumeSample(sample);
    }*/
virtual bool ConsumeSample(int16_t sample[2]) override {
    int16_t left = abs(sample[0]);
    int16_t right = abs(sample[1]);
    audioLevel = (left + right) / 2;

    Serial.printf("ConsumeSample: L=%d R=%d | Gain=%.2f | Level=%d\n",
                  sample[0], sample[1], currentGain, audioLevel);

    return AudioOutputI2S::ConsumeSample(sample);
}

    // Return the computed audio level.
    int getAudioLevel() {
        return audioLevel;
    }

private:
    int audioLevel;
    float currentGain;
};

#endif
