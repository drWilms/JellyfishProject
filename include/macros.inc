#ifndef MACROS_INC
#define MACROS_INC

// === Debugging Macros ===
#define DEBUG true

#if DEBUG
  #define LOG(fmt, ...) Serial.printf((String(fmt) + "\n").c_str(), ##__VA_ARGS__)
#else
  #define LOG(...)
#endif

// === Utility Macros ===
#define WAIT(x) FastLED.delay(x)

#endif // MACROS_INC