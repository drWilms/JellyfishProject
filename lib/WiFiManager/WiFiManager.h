// WiFiManager.h - Handles WiFi connection and reconnection
#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include "config.h"

class WiFiManager {
private:
    const char* ssid = WIFI_SSID;
    const char* password = WIFI_PASSWORD;
    bool connected = false;
    
    void attemptConnection();

public:
    WiFiManager();
    void begin();
    void loop();
    bool isConnected();
};

#endif // WIFIMANAGER_H