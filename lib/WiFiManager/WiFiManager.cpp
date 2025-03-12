#include "WiFiManager.h"
#include <Arduino.h>

/**
 * WiFiManager Implementation
 * Version: 2025-03-12
 */

WiFiManager::WiFiManager() : debugWiFi(true) {}  // Default: Debug enabled

void WiFiManager::begin() {
    if (debugWiFi) Serial.printf("[WiFi] Connecting to %s\n", WIFI_SSID);

    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ [WiFi] CONNECTED!");
        Serial.print("[WiFi] IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n❌ [WiFi] Connection FAILED.");
    }
}

void WiFiManager::reconnect() {
    if (debugWiFi) Serial.println("[WiFi] Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void WiFiManager::disconnect() {
    if (debugWiFi) Serial.println("[WiFi] Disconnecting...");
    WiFi.disconnect(true);
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::setDebug(bool enable) {
    debugWiFi = enable;
    Serial.printf("[WiFi] Debug mode %s.\n", debugWiFi ? "enabled" : "disabled");
}

bool WiFiManager::getDebug() const {
    return debugWiFi;
}
