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
    Serial.println("Server running");
}

void WiFiManager::onDisconnected()
{
    _connected = false;
    Serial.println("[WiFi] Disconnected.");
}

String WiFiManager::getStatus() const
{
    switch (WiFi.status())
    {
    case WL_IDLE_STATUS:
        return "Idle";
    case WL_NO_SSID_AVAIL:
        return "No SSID Available";
    case WL_SCAN_COMPLETED:
        return "Scan Completed";
    case WL_CONNECTED:
        return "Connected";
    case WL_CONNECT_FAILED:
        return "Connect Failed";
    case WL_CONNECTION_LOST:
        return "Connection Lost";
    case WL_DISCONNECTED:
        return "Disconnected";
    default:
        return "Unknown";
    }
}

String WiFiManager::getIPAddress() const
{
    return WiFi.localIP().toString();
}

int WiFiManager::getRSSI() const
{
    return WiFi.RSSI();
}

