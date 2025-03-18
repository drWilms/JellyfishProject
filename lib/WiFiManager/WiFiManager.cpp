#include "WiFiManager.h"

WiFiManager::WiFiManager() : timeClient(ntpUDP, "pool.ntp.org", 0, 60000) {}

void WiFiManager::connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    uint8_t attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(1000);
        Serial.print(".");
        attempts++;
    }
    Serial.println(WiFi.status() == WL_CONNECTED ? "\nWiFi Connected" : "\nWiFi Failed");
}

void WiFiManager::disconnect() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi Disconnected");
}

String WiFiManager::getDateTime() {
    connect();
    if (WiFi.status() == WL_CONNECTED) {
        timeClient.begin();
        timeClient.update();
        disconnect();
        return timeClient.getFormattedTime();
    }
    return "No Time";
}
