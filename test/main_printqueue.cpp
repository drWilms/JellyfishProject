#include "DynTimer.h"
#include "JellyfishQueue.h"

/**
 * ======================== Demo2 Specification ========================
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
 * Synchronization:
 * - "." and "," follow the same decrementing pattern as ":" and ";".
 * - "*" and "#" operate independently of the ":" and ";" cycle.
 * 
 * Queue Management:
 * - All printed characters will be queued in JellyfishQueue before printing.
 * 
 * End Condition:
 * - The program stops after 11 minutes.
 */

JellyfishQueue eventQueue;

// Print Cycle Control Variables
char currentChar = ':';  // Initial character
int repeatCount = 10;     // Initial repetition count
int mainCycleRepeats = 7; // Number of full cycles

// Symbol Print Cycle Control Variables
char symbolChar = '*';    // Initial symbol
int symbolRepeatCount = 5; // Initial repeat duration in minutes
int symbolCycleRepeats = 13; // Number of full symbol cycles

// Time Control
unsigned long programStartTime;
const unsigned long programDuration = 11 * 60 * 1000; // 11 minutes in milliseconds

// Function prototypes
void onMainCycle();
void onSymbolCycle();
void processQueue();

// Timers
DynTimer mainCycleTimer(1000, onMainCycle, true);    // Every second
DynTimer symbolCycleTimer(45000, onSymbolCycle, true); // Every 45 seconds
DynTimer queueProcessor(10, processQueue, true);    // Process queue every 10ms

void onMainCycle() {
    if (mainCycleRepeats == 0) return; // Stop if all cycles are done

    eventQueue.enqueue(std::string(1, currentChar)); // Queue the current character

    repeatCount--; // Reduce repetition count
    if (repeatCount == 0) { 
        // Switch character when reaching 0
        switch (currentChar) {
            case ':': currentChar = ';'; repeatCount = 9; break;
            case ';': currentChar = ':'; repeatCount = 8; break;
            case '.': currentChar = ','; repeatCount = 7; break;
            case ',': currentChar = '.'; repeatCount = 10; break;
        }

        // If we finished all patterns, reduce main cycle count
        if (repeatCount == 10 && currentChar == '.') {
            mainCycleRepeats--;
        }
    }
}

void onSymbolCycle() {
    if (symbolCycleRepeats == 0) return; // Stop if all cycles are done

    eventQueue.enqueue(std::string(1, symbolChar) + "\n"); // ✅ Symbols now print with newline

    symbolRepeatCount--; // Reduce repetition count
    if (symbolRepeatCount == 0) { 
        // Switch symbol when reaching 0
        switch (symbolChar) {
            case '*': symbolChar = '#'; symbolRepeatCount = 4; break;
            case '#': symbolChar = '*'; symbolRepeatCount = 3; break;
        }

        // If we finished all patterns, reduce symbol cycle count
        if (symbolRepeatCount == 5 && symbolChar == '*') {
            symbolCycleRepeats--;
        }
    }
}

void processQueue() {
    if (!eventQueue.isEmpty()) {
        std::string event = eventQueue.dequeue();
        Serial.print(event.c_str()); // ✅ Main cycle prints inline, symbols print with newline
    }

    // Stop program after 11 minutes
    if (millis() - programStartTime >= programDuration) {
        Serial.println("\n=== Program Ended ===");
        mainCycleTimer.stop();
        symbolCycleTimer.stop();
        queueProcessor.stop();
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("=== Demo2 Start ===");

    programStartTime = millis(); // Start time tracking

    mainCycleTimer.start();
    symbolCycleTimer.start();
    queueProcessor.start();
}

void loop() {
    mainCycleTimer.update();
    symbolCycleTimer.update();
    queueProcessor.update();
}
