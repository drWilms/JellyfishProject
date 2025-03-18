#include "LightManager.h"

LightManager::LightManager() : brightnessFactor(0), lastUpdateTime(0) {}

void LightManager::begin() {
    FastLED.addLeds<WS2812, PIN_RGB, LED_RGB_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
}

void LightManager::updateFadingEffect() {
    uint32_t currentTime = millis();

    if (currentTime - lastUpdateTime >= fadeInterval) {
        lastUpdateTime = currentTime;
        
        brightnessFactor += 0.05;
        if (brightnessFactor >= TWO_PI) brightnessFactor = 0;

        float brightness = (sin(brightnessFactor) + 1.0) / 2.0;
        uint8_t scaledBrightness = (uint8_t)(brightness * 255);

        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB(scaledBrightness, scaledBrightness, scaledBrightness);
        }
        FastLED.show();
    }
}

void LightManager::updateLight() {
    updateFadingEffect();
}
