#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "HWconfig.h"

class WiFiManager {
public:
    WiFiManager();
    void connect();
    void disconnect();
    String getDateTime(); // Fetches date/time
private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
};

#endif // WIFI_MANAGER_H
