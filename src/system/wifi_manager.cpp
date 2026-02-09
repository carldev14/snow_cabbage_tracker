#include "manager/system/wifi_manager.h"
#include "config/private/wifi_secrets.h" //* We'll define WIFI_SSID and WIFI_PASSWORD here if not provided

WiFiManager::WiFiManager()
    : _ssid(WIFI_SSID),
      _password(WIFI_PASSWORD),
      _connected(false),
      _lastAttemptTime(0),
      _attemptCount(0)
{
}

void WiFiManager::begin()
{
    delay(100); //* Small delay for serial stability
    Serial.println("[WiFi] Initializing WiFi...");

    //* Set WiFi mode to Station (client)
    WiFi.mode(WIFI_STA);

    //* Optional: set hostname
    String hostname = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    WiFi.setHostname(hostname.c_str());

    //* Start the connection process
    connect();
}

void WiFiManager::connect()
{
    Serial.printf("[WiFi] Connecting to: %s\n", _ssid);
    WiFi.begin(_ssid, _password);
    _lastAttemptTime = millis();
    _attemptCount++;
    _connected = false;

    WiFiManager::update();
}

void WiFiManager::update()
{
    //* Check the current status
    wl_status_t status = WiFi.status();

    if (status == WL_CONNECTED && !_connected)
    {
        onConnected();
    }
    else if (status != WL_CONNECTED && _connected)
    {
        onDisconnected();
    }

    //* If not connected and it's been more than 10 seconds since last attempt, try again
    if (!_connected && (millis() - _lastAttemptTime > 10000))
    {
        Serial.println("[WiFi] Reconnecting...");
        connect();
    }
}

void WiFiManager::onConnected()
{
    _connected = true;
    _attemptCount = 0;

    Serial.print("[WiFi] Connected! IP: ");
    Serial.println(WiFi.localIP());

    // ---- NTP CONFIG ----
    struct tm timeinfo;
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    setenv("TZ", "PHT-8", 1);
    tzset();
    Serial.println("[WiFi] Waiting for NTP time sync...");

    if (getLocalTime(&timeinfo, 10000))
    {
        // Initial Time. Until the delay lifted.
        _cachedTime = combineHourMin(timeinfo.tm_hour, timeinfo.tm_min);
        Serial.println("[TIME] " + _cachedTime);
        Serial.println("[WiFi] Time synchronized");
    }
    else
    {
        Serial.println("[WiFi] NTP sync failed");
    }

    Serial.println("Server running");
}

void WiFiManager::onDisconnected()
{
    _connected = false;
    Serial.println("[WiFi] Disconnected.");
}

String WiFiManager::getRealTime()
{
    // Wait and delay for 2 hours before
    unsigned long currentMillis = millis();
    if (currentMillis - _lastTimeUpdate >= TIME_INTERVAL)
    {
        _lastTimeUpdate = currentMillis;

        struct tm timeinfo;

        if (getLocalTime(&timeinfo))
        {
            _cachedTime = combineHourMin(timeinfo.tm_hour, timeinfo.tm_min);
        }
        else
        {
            _cachedTime = "";
        }
    }

    return _cachedTime;
}

String WiFiManager::combineHourMin(int hour, int min)
{
    char buffer[5]; // HHMM
    snprintf(buffer, sizeof(buffer), "%02d%02d", hour, min);
    return String(buffer);
}
