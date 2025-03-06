#ifndef MACROS_INC
#define MACROS_INC

// Debugging Macros
#define DEBUG 1  // Set to false to disable serial output

#define LOG(...) do { if (DEBUG) { Serial.printf(__VA_ARGS__); Serial.println(); } } while(0)



// Delay Macros
#define WAIT(x) FastLED.delay(x)

#endif  // MACROS_INC
