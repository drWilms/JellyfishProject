#include <Arduino.h>
#include "config.h"
#include "macros.inc"
#include <WiFi.h>  // ✅ Correct ESP32 WiFi library
#include "FifoDeque.h"
#include "QueueEvent.h"
#include "SWTimerManager.h"
#include "JellyfishLEDs.h"

FifoDeque eventQueue;
SWTimerManager timerManager;
JellyfishLEDs jellyfishLEDs;

SWTimer queueTimer(QUEUE_CHECK_INTERVAL);
SWTimer wifiTimer(WIFI_CHECK_INTERVAL);
SWTimer onBoardLEDTimer(LED_BLINK_INTERVAL);
SWTimer rgbBlinkTimer(RGB_BLINK_INTERVAL);
SWTimer rainbowTimer(RAINBOW_INTERVAL);

bool blueState = false;
uint8_t hue = 0;

void processQueueEvent() {
    if (eventQueue.isEmpty()) return;

    QueueEvent event = eventQueue.dequeue();

    switch (event.type) {
        case EventType::AUDIO:
            LOG("Playing audio...");
            break;

        case EventType::LIGHT:
            LOG("Handling light effect...");
            break;

        case EventType::TIMER:
            LOG("Timer event triggered...");
            break;

        case EventType::WIFI:
            LOG("Checking WiFi connection...");
            if (WiFi.status() != WL_CONNECTED) {
                LOG("WiFi not connected. Reconnecting...");
                WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            } else {
                LOG("WiFi already connected!");
            }
            break;
    }
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

    eventQueue.pushBack(createWiFiEvent());

    wifiTimer.start();
    timerManager.addTimer(wifiTimer, []() {
        eventQueue.pushBack(createWiFiEvent());
    });

    queueTimer.start();
    timerManager.addTimer(queueTimer, processQueueEvent);

    onBoardLEDTimer.start();
    timerManager.addTimer(onBoardLEDTimer, toggleOnboardLED);

    rgbBlinkTimer.start();
    timerManager.addTimer(rgbBlinkTimer, toggleRGBBlue);

    rainbowTimer.start();
    timerManager.addTimer(rainbowTimer, updateRainbow);

    LOG("Timers initialized");
}

void loop() {
    timerManager.update();
    WAIT(1000);
}
