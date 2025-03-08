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
    Serial.printf("Queue size before dequeuing: %d\n", queue.size());
    if (queue.isEmpty()) return;
    std::string event = queue.dequeue();
    Serial.printf("Processing queue event: %s\n", event.c_str());
}

void toggleOnboardLED() {
    static bool state = false;
    state = !state;
    digitalWrite(LED_PIN, state);
    Serial.printf("Toggling Onboard LED at %lu\n", millis());
}

void setup() {
    Serial.begin(115200);
    Serial.println("Jellyfish Project: Startup");

    pinMode(LED_PIN, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("WiFi Connecting...");

    queue.enqueue("/track1.mp3");

    timerManager.addSlowTimer(slowTimer, processQueueEvent);
    timerManager.addFastTimer(fastTimer, toggleOnboardLED);

    Serial.println("Timers initialized with hierarchy");
}

void loop() {
    timerManager.update();
    delay(1000);
}
