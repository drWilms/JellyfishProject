#include "DynTimer.h"
#include "JellyfishQueue.h"

JellyfishQueue eventQueue;

// Function prototype
void onTimer();

// ✅ Corrected: Timer must update in loop()
DynTimer timer(500, onTimer, true);  

void onTimer() {
    Serial.println("Timer fired!");
    eventQueue.enqueue("TIMER_EXPIRED"); // ✅ Always enqueue the event
}

void setup() {
    Serial.begin(115200);
    Serial.println("=== Timer Queue Debug Start ===");

    Serial.println("Starting timer...");
    timer.start(); // ✅ Start the repeating timer
}

void loop() {
    // ✅ Fix: Ensure the timer actually fires
    timer.update();  

    if (!eventQueue.isEmpty()) {
        std::string event = eventQueue.dequeue();
        Serial.printf("Processing event: %s\n", event.c_str());

        if (event == "TIMER_EXPIRED") {
            Serial.println("Event recognized: TIMER_EXPIRED");
            // ✅ No need to restart the timer—it’s already repeating
        }
    }

    delay(10); // ✅ Prevents excessive Serial output
}
