/*
 * DynTimer.cpp - Implements a simple software timer
 * Version: 2025-03-14
 */

 #include "DynTimer.h"

 // Constructor
 DynTimer::DynTimer() {
     interval = 0;
     lastRun = 0;
     active = false;
 }
 
 // Start the timer with a given duration
 void DynTimer::start(unsigned long duration) {
     interval = duration;
     lastRun = millis();
     active = true;
 }
 
 // Stop the timer
 void DynTimer::stop() {
     active = false;
 }
 
 // Check if the timer has expired
 bool DynTimer::isExpired() {
     if (!active) return false;
     return (millis() - lastRun) >= interval;
 }
 
 // Check if the timer is active
 bool DynTimer::isActive() const {
     return active;
 }
 