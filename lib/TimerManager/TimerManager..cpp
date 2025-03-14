/*
 * TimerManager.cpp - Implements the TimerManager for handling multiple tiers of timers
 * Version: 2025-03-14
 */

 #include "TimerManager.h"

 TimerManager::TimerManager() {
     // Initialize all timers
     for (int i = 0; i < MAX_ULTRAFAST_TIMERS; i++) {
         ultraFastTimers[i] = DynTimer();
         ultraFastCallbacks[i] = nullptr;
         ultraFastDurations[i] = 0;
     }
     for (int i = 0; i < MAX_FAST_TIMERS; i++) {
         fastTimers[i] = DynTimer();
         fastCallbacks[i] = nullptr;
         fastDurations[i] = 0;
     }
     for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
         mediumTimers[i] = DynTimer();
         mediumCallbacks[i] = nullptr;
         mediumDurations[i] = 0;
     }
     for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
         slowTimers[i] = DynTimer();
         slowCallbacks[i] = nullptr;
         slowDurations[i] = 0;
     }
 }
 
 // Function to start an UltraFast Timer
 int TimerManager::startUltraFastTimer(unsigned long duration, TimerCallback callback) {
     for (int i = 0; i < MAX_ULTRAFAST_TIMERS; i++) {
         if (!ultraFastTimers[i].isActive()) {  // Correcte methode
             ultraFastTimers[i].start(duration);  // Correcte methode
             ultraFastCallbacks[i] = callback;
             ultraFastDurations[i] = duration;
             return i;
         }
     }
     return -1; // No available slot
 }
 
 // Function to start a Fast Timer
 int TimerManager::startFastTimer(unsigned long duration, TimerCallback callback) {
     for (int i = 0; i < MAX_FAST_TIMERS; i++) {
         if (!fastTimers[i].isActive()) {
             fastTimers[i].start(duration);
             fastCallbacks[i] = callback;
             fastDurations[i] = duration;
             return i;
         }
     }
     return -1;
 }
 
 // Function to start a Medium Timer
 int TimerManager::startMediumTimer(unsigned long duration, TimerCallback callback) {
     for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
         if (!mediumTimers[i].isActive()) {
             mediumTimers[i].start(duration);
             mediumCallbacks[i] = callback;
             mediumDurations[i] = duration;
             return i;
         }
     }
     return -1;
 }
 
 // Function to start a Slow Timer
 int TimerManager::startSlowTimer(unsigned long duration, TimerCallback callback) {
     for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
         if (!slowTimers[i].isActive()) {
             slowTimers[i].start(duration);
             slowCallbacks[i] = callback;
             slowDurations[i] = duration;
             return i;
         }
     }
     return -1;
 }
 
 // Function to update all timers
 void TimerManager::updateTimers() {
     for (int i = 0; i < MAX_ULTRAFAST_TIMERS; i++) {
         if (ultraFastTimers[i].isExpired()) {
             if (ultraFastCallbacks[i]) ultraFastCallbacks[i]();
             ultraFastTimers[i].start(ultraFastDurations[i]);  // Correcte methode
         }
     }
     for (int i = 0; i < MAX_FAST_TIMERS; i++) {
         if (fastTimers[i].isExpired()) {
             if (fastCallbacks[i]) fastCallbacks[i]();
             fastTimers[i].start(fastDurations[i]);
         }
     }
     for (int i = 0; i < MAX_MEDIUM_TIMERS; i++) {
         if (mediumTimers[i].isExpired()) {
             if (mediumCallbacks[i]) mediumCallbacks[i]();
             mediumTimers[i].start(mediumDurations[i]);
         }
     }
     for (int i = 0; i < MAX_SLOW_TIMERS; i++) {
         if (slowTimers[i].isExpired()) {
             if (slowCallbacks[i]) slowCallbacks[i]();
             slowTimers[i].start(slowDurations[i]);
         }
     }
 }
 