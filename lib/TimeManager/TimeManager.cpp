/**
 * @file TimeManager.cpp
 * @brief Manages time synchronization and local time correction for Amsterdam.
 * @author Jan Wilms
 * @date Created on: 2025-03-16 15:05 (Amsterdam Time)
 */

 #include "TimeManager.h"
 #include <WiFi.h>
 #include <NTPClient.h>
 #include <WiFiUdp.h>
 #include "HWconfig.h"

 
 WiFiUDP ntpUDP;
 NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);
 
 TimeManager::TimeManager() : timeSyncRequested(false) {}
 
 void TimeManager::requestTimeSync() {
     timeSyncRequested = true;
 }
 
 bool TimeManager::isTimeSyncPending() {
     return timeSyncRequested;
 }
 
 void TimeManager::syncTime() {
     Serial.println("[INFO] Syncing time with NTP...");
     timeSyncRequested = false;
 
     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
     uint8_t attempts = 0;
     while (WiFi.status() != WL_CONNECTED && attempts < 10) {
         delay(1000);
         Serial.print(".");
         attempts++;
     }
 
     if (WiFi.status() == WL_CONNECTED) {
         timeClient.begin();
         timeClient.update();
         WiFi.disconnect();
         WiFi.mode(WIFI_OFF);
 
         time_t rawTime = timeClient.getEpochTime();
         struct tm timeInfo;
         gmtime_r(&rawTime, &timeInfo);
 
         if (isDST(timeInfo)) {
             rawTime += 3600;  // Adjust for DST
             gmtime_r(&rawTime, &timeInfo);
         }
 
         char buffer[32];
         strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
         Serial.print("Updated Local Time: ");
         Serial.println(buffer);
     } else {
         Serial.println("[ERROR] NTP Sync Failed!");
     }
 }
 
 String TimeManager::getLocalDateTime() {
     time_t now = timeClient.getEpochTime();
     struct tm timeInfo;
     gmtime_r(&now, &timeInfo);
 
     if (isDST(timeInfo)) {
         now += 3600;
         gmtime_r(&now, &timeInfo);
     }
 
     char buffer[32];
     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
     return String(buffer);
 }
 
 bool TimeManager::isDST(struct tm timeInfo) {
    // Amsterdam follows CET (UTC+1) and CEST (UTC+2 during DST)
    // DST starts last Sunday of March, ends last Sunday of October

    int year = timeInfo.tm_year + 1900;
    int month = timeInfo.tm_mon + 1;
    int day = timeInfo.tm_mday;
    int hour = timeInfo.tm_hour;
    int weekday = timeInfo.tm_wday;  // Sunday = 0

    if (month < 3 || month > 10) return false; // January, February, November, December = Standard Time (UTC+1)
    if (month > 3 && month < 10) return true;  // April to September = DST (UTC+2)

    // Check last Sunday of March (DST starts)
    if (month == 3) {
        int lastSunday = day - weekday;
        return lastSunday >= 25 && hour >= 2;  // DST starts at 02:00
    }

    // Check last Sunday of October (DST ends)
    if (month == 10) {
        int lastSunday = day - weekday;
        return lastSunday >= 25 && hour < 2;  // Standard Time starts at 03:00
    }

    return true; // Default to DST if uncertain
}
