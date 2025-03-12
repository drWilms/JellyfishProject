#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>  // Ensure inclusion of WiFi functions
#include "config.h"

/**
 * WiFiManager - Handles WiFi connection, disconnection, and reconnection.
 * Version: 2025-03-12
 */

class WiFiManager {
private:
    bool debugWiFi;  // Debug flag

public:
    WiFiManager();
    void begin();       // Connect to WiFi at startup
    void reconnect();   // Reconnects if disconnected
    void disconnect();  // Forces WiFi disconnection
    bool isConnected(); // Returns true if connected
    void setDebug(bool enable);
    bool getDebug() const;
};

#endif // WIFI_MANAGER_H
