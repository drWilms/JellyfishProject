#include "DynTimer.h"
#include "JellyfishQueue.h"
#include "config.h"
#include <vector>

/**
 * ======================== Demo3 Specification ========================
 *
 * Main Print Cycle (":" and ";"):
 * - Every 1 second, print ":" 10 times.
 * - Then switch to ";" for 9 times.
 * - Then switch back to ":" for 8 times.
 * - Continue decreasing until 0.
 * - At 0, switch to "." for 10 times, "," for 7 times, following the same decreasing pattern.
 * - This full cycle repeats 7 times.
 *
 * Secondary Print Cycle ("*" and "#"):
 * - Every 45 seconds, print "*" for 5 minutes.
 * - Then switch "*" → "#" for 4 minutes.
 * - Then switch back to "*" for 3 minutes.
 * - This full cycle repeats 13 times.
 *
 * LED Blink Cycle:
 * - LED on PIN 2 blinks with a cycle of 20ms OFF and 17ms ON.
 *
 * Synchronization:
 * - "." and "," follow the same decrementing pattern as ":" and ";".
 * - "*" and "#" operate independently of the ":" and ";" cycle.
 *
 * Queue Management:
 * - All printed characters will be queued in JellyfishQueue before printing.
 *
 * Timer Management:
 * - Uses TimerManager to dynamically allocate and manage timers.
 *
 * End Condition:
 * - The program stops after 11 minutes.
 */

JellyfishQueue eventQueue;
TimerManager timerManager;

// Print Cycle Control Variables
char currentChar = ':';
int repeatCount = 10;
int mainCycleRepeats = 7;

// Symbol Print Cycle Control Variables
char symbolChar = '*';
int symbolRepeatCount = 5;
int symbolCycleRepeats = 13;

// LED Blink Control Variables
bool ledState = false;
void toggleLED();
int ledBlinkTimerNr;

// Time Control
unsigned long programStartTime;
const unsigned long programDuration = 11 * 60 * 1000;

// Function prototypes
void onMainCycle();
void onSymbolCycle();
void processQueue();

void toggleLED() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    DynTimer* ledTimer = timerManager.getTimer(ledBlinkTimerNr);
    if (ledTimer) {
        ledTimer->setInterval(ledState ? 17 : 20);
    }
}

void onMainCycle() {
    if (mainCycleRepeats == 0) return;
    eventQueue.enqueue(std::string(1, currentChar));
    repeatCount--;
    if (repeatCount == 0) {
        switch (currentChar) {
            case ':': currentChar = ';'; repeatCount = 9; break;
            case ';': currentChar = ':'; repeatCount = 8; break;
            case '.': currentChar = ','; repeatCount = 7; break;
            case ',': currentChar = '.'; repeatCount = 10; break;
        }
        if (repeatCount == 10 && currentChar == '.') {
            mainCycleRepeats--;
        }
    }
}

void onSymbolCycle() {
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

void processQueue() {
    if (!eventQueue.isEmpty()) {
        std::string event = eventQueue.dequeue();
        Serial.print(event.c_str());
    }
    if (millis() - programStartTime >= programDuration) {
        Serial.println("\n=== Program Ended ===");
        timerManager.stopAll();
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("=== Demo3 Start ===");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    programStartTime = millis();

    timerManager.addTimer(1000, onMainCycle, true);
    timerManager.addTimer(45000, onSymbolCycle, true);
    timerManager.addTimer(10, processQueue, true);
    ledBlinkTimerNr = timerManager.addTimer(20, toggleLED, true);
}

void loop() {
    timerManager.updateAll();
}
