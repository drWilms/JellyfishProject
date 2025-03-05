#ifndef MACROS_INC
#define MACROS_INC

// Debugging Macros
#define DEBUG true  // Set to false to disable serial output

#define LOG(...) if (DEBUG) { Serial.print(__VA_ARGS__); Serial.println(); }

// Delay Macros
#define WAIT(x) FastLED.delay(x)

#endif  // MACROS_INC
