#include "manager/system/wifi_manager.h"
#include "config/private/wifi_secrets.h"

// Define TIME_INTERVAL if not in header
#ifndef TIME_INTERVAL
#define TIME_INTERVAL (2 * 60 * 60 * 1000UL) // 2 hours in milliseconds
#endif

WiFiManager::WiFiManager()
    : _ssid(WIFI_SSID),
      _password(WIFI_PASSWORD),
      _connected(false),
      _lastAttemptTime(0),
      _attemptCount(0),
      _lastTimeUpdate(0) // CRITICAL: Initialize this!
{
    // Initialize the time buffer with a safe default
    strncpy(_cachedTime, "0000", sizeof(_cachedTime));
    _cachedTime[sizeof(_cachedTime) - 1] = '\0';
}

void WiFiManager::begin()
{
    delay(100);
    Serial.println("[WiFi] Initializing WiFi...");

    // Set WiFi mode to Station
    WiFi.mode(WIFI_STA);

    // FIXED: Eliminate String concatenation for hostname
    char hostname[32]; // Static buffer instead of String
    uint64_t chipId = ESP.getEfuseMac();
    snprintf(hostname, sizeof(hostname), "ESP32-%04X%08X",
             (uint16_t)(chipId >> 32), (uint32_t)chipId);
    WiFi.setHostname(hostname);

    // Start connection (non-recursive)
    connect();
}
void WiFiManager::disconnect()
{
    if (WiFi.isConnected())
    {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }
}

void WiFiManager::connect()
{
    if (_attemptCount > 0)
    {
        Serial.printf("[WiFi] Attempt %d to connect to: %s\n", _attemptCount + 1, _ssid);
    }
    else
    {
        Serial.printf("[WiFi] Connecting to: %s\n", _ssid);
    }

    WiFi.disconnect(true); // Clean disconnect first
    delay(100);

    WiFi.begin(_ssid, _password);
    _lastAttemptTime = millis();
    _attemptCount++;
    _connected = false;

    // NO recursive call to update() here!
}

void WiFiManager::update()
{
    // Add throttle to prevent excessive checking
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck < 500 && lastCheck != 0)
        return;
    lastCheck = millis();

    wl_status_t status = WiFi.status();

    if (status == WL_CONNECTED && !_connected)
    {
        onConnected();
    }
    else if (status != WL_CONNECTED && _connected)
    {
        onDisconnected();
    }

    // If not connected and it's been more than 15 seconds
    if (!_connected && (millis() - _lastAttemptTime > 15000))
    {
        if (_attemptCount < 5)
        {
            Serial.println("[WiFi] Reconnecting...");
            connect();
        }
        else
        {
            Serial.println("[WiFi] Too many attempts, restarting...");
            delay(2000);
            ESP.restart();
        }
    }
}

void WiFiManager::onConnected()
{
    _connected = true;
    _attemptCount = 0;

    Serial.print("[WiFi] Connected! IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("[WiFi] RSSI: ");
    Serial.println(WiFi.RSSI());

    // Configure NTP
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    setenv("TZ", "PHT-8", 1);
    tzset();

    Serial.println("[WiFi] Waiting for NTP time sync...");

    struct tm timeinfo;
    if (getLocalTime(&timeinfo, 10000))
    {
        // FIXED: Direct formatting - NO String objects
        snprintf(_cachedTime, sizeof(_cachedTime), "%02d%02d",
                 timeinfo.tm_hour, timeinfo.tm_min);
        _lastTimeUpdate = millis(); // Initialize the timer

        Serial.print("[TIME] Initial time: ");
        Serial.println(_cachedTime);

        // ? Change isTimeSynchronized to true
        // ? To condition in the main logic. So if the value is false (Not initialized), it won't run, otherwise it will.
        isTimeSynchronized = true;
        Serial.println("[WiFi] Time synchronized successfully");
    }
    else
    {
        Serial.println("[WiFi] NTP sync failed, using default time");
    }

    Serial.println("Server running");
}

void WiFiManager::onDisconnected()
{
    _connected = false;
    Serial.println("[WiFi] Disconnected.");
}

const char *WiFiManager::getRealTime()
{
    unsigned long currentMillis = millis();

    if (_lastTimeUpdate == 0 || (currentMillis - _lastTimeUpdate >= TIME_INTERVAL))
    {
        _lastTimeUpdate = currentMillis;
        struct tm timeinfo;

        if (getLocalTime(&timeinfo, 1000))
        {
            snprintf(_cachedTime, sizeof(_cachedTime), "%02d%02d",
                     timeinfo.tm_hour, timeinfo.tm_min);
        }
        // If NTP fails, keep the existing cached time
    }

    return _cachedTime;
}
