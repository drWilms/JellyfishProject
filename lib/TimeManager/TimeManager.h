/**
 * @file TimeManager.h
 * @brief Manages time synchronization and local time correction for Amsterdam.
 * @author Jan Wilms
 * @date Created on: 2025-03-16 14:30 (Amsterdam Time)
 */

 #ifndef TIMEMANAGER_H
 #define TIMEMANAGER_H
 
 #include <Arduino.h>
 
 class TimeManager {
 public:
     TimeManager();
     void requestTimeSync();
     void syncTime();
     bool isTimeSyncPending();
     String getLocalDateTime();
 
 private:
     volatile bool timeSyncRequested;
     bool isDST(struct tm timeInfo);  // ✅ FIX: Declare isDST()
 };
 
 #endif // TIMEMANAGER_H
 