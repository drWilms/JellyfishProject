// WiFiManager.cpp - Implements WiFi connection and reconnection logic
#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager() {
    WiFi.mode(WIFI_STA);
}

void WiFiManager::begin() {
    Serial.println("[WiFi] Connecting to " + String(ssid));
    attemptConnection();
}

void WiFiManager::attemptConnection() {
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try for 10 seconds
        delay(500);
        Serial.println("[WiFi] Connecting...");
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        Serial.println("[WiFi] Connected! IP: " + WiFi.localIP().toString());
    } else {
        Serial.println("[WiFi] Connection failed. Retrying later...");
    }
}

void WiFiManager::loop() {
    if (!connected && millis() % 3600000 < 5000) { // Check every hour
        attemptConnection();
    }
}

bool WiFiManager::isConnected() {
    return connected;
}