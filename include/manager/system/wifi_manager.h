#pragma once

#include <WiFi.h>

class WiFiManager
{
public:
    //* Constructor: optionally takes SSID and password, or uses defaults from config.h
    WiFiManager();

    //* Initialize WiFi connection
    void begin();

    //* Update function to be called in the main loop (for handling reconnection, etc.)
    void update();

    //* Get the current connection status as a string
    String getStatus() const;

    //* Get the IP address as a string
    String getIPAddress() const;

    //* Get the RSSI (signal strength)
    int getRSSI() const;

    void debugNetworkInfo();

    /**
     * @brief Get the current system time in HHMM format.
     *
     * Note: The time is based on military time.
     * - Hours are from 0 to 23.
     * - Returns a String in HHMM format (e.g., "1905" for 7:05 PM)
     * - Updates only every TIME_INTERVAL milliseconds for performance.
     *
     * @return String Current time as HHMM.
     */
    String getRealTime();

private:
    const char *_ssid;
    const char *_password;
    String combineHourMin(int hour, int min);
    bool _connected;
    unsigned long _lastTimeUpdate = 0;
    const unsigned long TIME_INTERVAL = 1000 * 60 * 3; // 3 hours
    String _cachedTime = "----";
    unsigned long _lastAttemptTime;
    int _attemptCount;

    void connect();
    void onConnected();
    void onDisconnected();
};
