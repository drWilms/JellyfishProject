#ifndef MACROS_INC
#define MACROS_INC

// Debugging Macros
#define DEBUG true  // Set to false to disable serial output
#define LOG(x) if (DEBUG) { Serial.println(x); }

// Delay Macros
#define WAIT(x) delay(x)

#endif
