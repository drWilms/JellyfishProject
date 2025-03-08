// ========================= main.cpp =========================
#include <Arduino.h>
#include "config.h"
#include "macros.inc"
#include <WiFi.h>
#include "JellyfishQueue.h"
#include "HierarchicalTimerManager.h"
#include "JellyfishLEDs.h"

JellyfishQueue queue;
HierarchicalTimerManager timerManager;
JellyfishLEDs jellyfishLEDs;

// Define timers based on the new hierarchy
SWTimer slowTimer(SLOW_TIMER_INTERVAL);
SWTimer fastTimer(FAST_TIMER_INTERVAL);
SWTimer ultraFastTimer(ULTRAFAST_TIMER_INTERVAL);

bool blueState = false;
uint8_t hue = 0;

void processQueueEvent() {
    if (queue.isEmpty()) return;
    std::string event = queue.dequeue();
    LOG("Processing queue event: ", event.c_str());
}

void toggleOnboardLED() {
    static bool state = false;
    state = !state;
    digitalWrite(LED_PIN, state);
    LOG("Toggling Onboard LED");
}

void toggleRGBBlue() {
    blueState = !blueState;
    jellyfishLEDs.setSingleColor(0, blueState ? CRGB::Blue : CRGB::Black);
}

void updateRainbow() {
    hue += 10;
}

void setup() {
    Serial.begin(115200);
    LOG("Jellyfish Project: Startup");

    pinMode(LED_PIN, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    LOG("WiFi Connecting...");

    queue.enqueue("/track1.mp3");

    // Assign timers to their categories
    timerManager.addSlowTimer(slowTimer, processQueueEvent);
    timerManager.addFastTimer(fastTimer, toggleOnboardLED);
    timerManager.addUltraFastTimer(ultraFastTimer, updateRainbow);

    LOG("Timers initialized with hierarchy");
}

void loop() {
    timerManager.update();
    WAIT(1000);
}
