#include "DynTimer.h"
#include "JellyfishQueue.h"
#include "WiFiManager.h"
#include "config.h"
#include <vector>

/**
 * ======================== Demo4 Specification ========================
 *
 * - WiFi connects at startup, with **automatic reconnection** every 6 minutes.
 * - WiFi **forcibly disconnects every 2 minutes** and **reconnects after 23 seconds**.
 * - Maintains **continuous LED blinking** on PIN 2.
 * - Implements **print queuing**, managing character sequences at set intervals.
 * - Uses **DynTimer for precise, non-blocking scheduling**.
 */

JellyfishQueue eventQueue;
TimerManager timerManager;
WiFiManager wifiManager;

// LED Blink Control
bool ledState = false;
void toggleLED();
int ledBlinkTimerNr;

// Function prototypes
void printCycle();
void processQueue();
void manageWiFi();
void forceWiFiDisconnect();
void reconnectWiFi();

// WiFi Control Timers
int forceDisconnectTimerNr;
int wifiReconnectTimerNr;

void toggleLED() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    DynTimer* ledTimer = timerManager.getTimer(ledBlinkTimerNr);
    if (ledTimer) {
        ledTimer->setInterval(ledState ? 17 : 20);
    }
}

void printCycle() {
    static char currentChar = ':';
    static int repeatCount = 10;
    
    if (repeatCount > 0) {
        eventQueue.enqueue(std::string(1, currentChar));
        repeatCount--;
    } else {
        switch (currentChar) {
            case ':': currentChar = ';'; repeatCount = 9; break;
            case ';': currentChar = ':'; repeatCount = 8; break;
            case '.': currentChar = ','; repeatCount = 7; break;
            case ',': currentChar = '.'; repeatCount = 10; break;
        }
    }
}

void onSymbolCycle() {
    static char symbolChar = '*';
    static int symbolRepeatCount = 5;
    static int symbolCycleRepeats = 13;

    if (symbolCycleRepeats == 0) return;

    eventQueue.enqueue(std::string(1, symbolChar) + "\n");

    symbolRepeatCount--;

    if (symbolRepeatCount == 0) {
        switch (symbolChar) {
            case '*': symbolChar = '#'; symbolRepeatCount = 4; break;
            case '#': symbolChar = '*'; symbolRepeatCount = 3; break;
        }
        if (symbolRepeatCount == 5 && symbolChar == '*') {
            symbolCycleRepeats--;
        }
    }
}

void manageWiFi() {
    Serial.println("[WiFi] Checking connection...");
    wifiManager.reconnect();
}

void forceWiFiDisconnect() {
    Serial.println("[WiFi] FORCING DISCONNECT...");
    wifiManager.disconnect();
    wifiReconnectTimerNr = timerManager.addTimer(23000, reconnectWiFi, false); // Reconnect after 23 seconds
}

void reconnectWiFi() {
    Serial.println("[WiFi] RECONNECTING NOW...");
    wifiManager.reconnect();
}

void setup() {
    Serial.begin(115200);
    Serial.println("=== Demo4 Start ===");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    wifiManager.begin();  // Connect to WiFi at startup

    // Print Cycles
    timerManager.addTimer(1000, printCycle, true);
    timerManager.addTimer(45000, onSymbolCycle, true);  // Restore symbol printing  
    timerManager.addTimer(10, [&] { eventQueue.processQueue(); }, true);


    // LED Blinking
    ledBlinkTimerNr = timerManager.addTimer(20, toggleLED, true);

    // WiFi management
    timerManager.addTimer(6 * 60 * 1000, manageWiFi, true);
    forceDisconnectTimerNr = timerManager.addTimer(2 * 60 * 1000, forceWiFiDisconnect, true);
}

void loop() {
    timerManager.updateAll();
}
