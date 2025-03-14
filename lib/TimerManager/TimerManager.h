/*
 * TimerManager.h - Manages 4 independent timer tiers
 * Version: 2025-03-14
 * 
 * Timers:
 * - UltraFast ( < 50ms )
 * - Fast ( 50 - 999ms )
 * - Medium ( 1s - 9s )
 * - Slow ( 10s+ )
 *
 * Timers are automatically managed and restarted.
 */

 #ifndef TIMERMANAGER_H
 #define TIMERMANAGER_H
 
 #include "Arduino.h"
 #include "DynTimer.h"
 
 #define MAX_ULTRAFAST_TIMERS 5
 #define MAX_FAST_TIMERS 5
 #define MAX_MEDIUM_TIMERS 5
 #define MAX_SLOW_TIMERS 5
 
 typedef void (*TimerCallback)();
 
 class TimerManager {
 private:
     // UltraFast Timers
     DynTimer ultraFastTimers[MAX_ULTRAFAST_TIMERS];
     TimerCallback ultraFastCallbacks[MAX_ULTRAFAST_TIMERS];
     unsigned long ultraFastDurations[MAX_ULTRAFAST_TIMERS];
     
     // Fast Timers
     DynTimer fastTimers[MAX_FAST_TIMERS];
     TimerCallback fastCallbacks[MAX_FAST_TIMERS];
     unsigned long fastDurations[MAX_FAST_TIMERS];
 
     // Medium Timers
     DynTimer mediumTimers[MAX_MEDIUM_TIMERS];
     TimerCallback mediumCallbacks[MAX_MEDIUM_TIMERS];
     unsigned long mediumDurations[MAX_MEDIUM_TIMERS];
 
     // Slow Timers
     DynTimer slowTimers[MAX_SLOW_TIMERS];
     TimerCallback slowCallbacks[MAX_SLOW_TIMERS];
     unsigned long slowDurations[MAX_SLOW_TIMERS];
 
 public:
     TimerManager();
     
     int startUltraFastTimer(unsigned long duration, TimerCallback callback);
     int startFastTimer(unsigned long duration, TimerCallback callback);
     int startMediumTimer(unsigned long duration, TimerCallback callback);
     int startSlowTimer(unsigned long duration, TimerCallback callback);
     
     void updateTimers();
 };
 
 #endif // TIMERMANAGER_H