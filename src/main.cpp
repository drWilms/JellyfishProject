#include "DynTimer.h"
#include "JellyfishQueue.h"
#include "WiFiManager.h"
#include "config.h"
#include <vector>

/**
 * ======================== Demo5 - Fully Timed Queue-Based Printing ========================
 *
 * - WiFi connects at startup, **auto-reconnects every 6 minutes**.
 * - WiFi **disconnects every 2 minutes**, reconnects **after 23 seconds**.
 * - **LED on PIN 2 blinks continuously** (20ms OFF, 17ms ON).
 * - **Each individual print character is separately queued with a timed task**.
 * - **DynTimer schedules every event separately**.
 * - **Follows original Demo4 print cycle exactly, but with granular task-based execution.**
 */

JellyfishQueue eventQueue;
TimerManager timerManager;
WiFiManager wifiManager;

// LED Blink Control
bool ledState = false;
void toggleLED();
int ledBlinkTimerNr;

// Function prototypes
void queueMainPrintSequence();
void queueSymbolPrintSequence();
void enqueueCharacter(char c);
void forceWiFiDisconnect();
void reconnectWiFi();

// WiFi Control Timers
int forceDisconnectTimerNr;
int wifiReconnectTimerNr;

// Print Cycle Variables (kept global for individual task scheduling)
char mainCycleChars[] = {':', ';', ':', ';', '.', ','};
int mainCycleCounts[] = {10, 9, 8, 7, 10, 7};
int mainCycleIndex = 0;
int mainCycleRepeat = 7;

char symbolCycleChars[] = {'*', '#', '*'};
int symbolCycleCounts[] = {5, 4, 3};
int symbolCycleIndex = 0;
int symbolCycleRepeat = 13;

/**
 * Queues individual characters at scheduled intervals.
 */
void enqueueCharacter(char c) {
    eventQueue.enqueue(std::string(1, c));
}

/**
 * Schedules an entire sequence of characters in the main print cycle.
 */
void queueMainPrintSequence() {
    if (mainCycleRepeat == 0) return;

    char currentChar = mainCycleChars[mainCycleIndex];
    int repeatCount = mainCycleCounts[mainCycleIndex];

    for (int i = 0; i < repeatCount; i++) {
        timerManager.addTimer(i * 100, [currentChar]() { enqueueCharacter(currentChar); }, false);
    }

    mainCycleIndex++;
    if (mainCycleIndex >= 6) {
        mainCycleIndex = 0;
        mainCycleRepeat--;
    }
}

void queueSymbolPrintSequence() {
    if (symbolCycleRepeat == 0) return;

    char currentChar = symbolCycleChars[symbolCycleIndex];
    int repeatCount = symbolCycleCounts[symbolCycleIndex];

    for (int i = 0; i < repeatCount; i++) {
        timerManager.addTimer(i * 500, [currentChar]() { enqueueCharacter(currentChar); }, false);
    }

    symbolCycleIndex++;
    if (symbolCycleIndex >= 3) {
        symbolCycleIndex = 0;
        symbolCycleRepeat--;
    }
}

/**
 * Toggles the LED on PIN 2 with dynamic timing.
 */
void toggleLED() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    DynTimer* ledTimer = timerManager.getTimer(ledBlinkTimerNr);
    if (ledTimer) {
        ledTimer->setInterval(ledState ? 17 : 20);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== Demo5 - Queue Everything Start ===");
    delay(4000);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    wifiManager.begin();  // Connect to WiFi at startup
    wifiManager.setDebug(false);

    // **Queue-based structured printing (original decreasing pattern)**
    timerManager.addTimer(1000, queueMainPrintSequence, true);
    timerManager.addTimer(45000, queueSymbolPrintSequence, true);

    // Queue Processing Task (pulls and prints characters)
    timerManager.addTimer(10, [] { eventQueue.processQueue(); }, true);
    timerManager.setDebug(false);
    // LED Blink Task
    ledBlinkTimerNr = timerManager.addTimer(20, toggleLED, true);
}

void loop() {
    unsigned long startTime = millis();
    timerManager.updateAll();

    // 🚨 Voorkom WDT-reset door een kleine vertraging in te bouwen
    if (millis() - startTime > 50) {
        Serial.println("[WARNING] loop() took too long! Adding small delay.");
        delay(1);  // Geeft de ESP32 tijd om andere taken af te handelen
    }
}

