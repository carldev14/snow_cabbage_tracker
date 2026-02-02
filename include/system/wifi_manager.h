#pragma once

#include <WiFi.h>

class WiFiManager
{
public:
    // Constructor: optionally takes SSID and password, or uses defaults from config.h
    WiFiManager();

    // Initialize WiFi connection
     void begin();

    // Update function to be called in the main loop (for handling reconnection, etc.)
    void update();

    // Get the current connection status as a string
    String getStatus() const;

    // Get the IP address as a string
    String getIPAddress() const;

    // Get the RSSI (signal strength)
    int getRSSI() const;
    void debugNetworkInfo();
private:
    const char *_ssid;
    const char *_password;
    bool _connected;
    unsigned long _lastAttemptTime;
    int _attemptCount;

    void connect();
    void onConnected();
    void onDisconnected();
};
