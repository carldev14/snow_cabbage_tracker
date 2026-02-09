#include "config/system_config.h"

ServerManager::ServerManager() : server(80)
{
    //* Constructor
}

void ServerManager::serveFile(String basePath, String path)
{
    server.on(basePath.c_str(), HTTP_GET, [path, this](AsyncWebServerRequest *request)
              {
    if (!SPIFFS.exists(path))
    {
        request->send(404, "text/plain", "File not found: " + path);
        return;
    }
    const String mimeType = this->getMimeType(path);
    File file = SPIFFS.open(path, "r");
    if (!file)
    {
        request->send(500, "text/plain", "Failed to open file");
        return;
    }
        
    request->send(file, path, mimeType, false); });
}

void ServerManager::begin()
{
    //* Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed!");
        return;
    }

    Serial.println("SPIFFS mounted");
    //* //* Debug: List all files in SPIFFS
    //* Serial.println("Files in SPIFFS:");
    //* File root = SPIFFS.open("/");
    //* File file = root.openNextFile();
    //* while (file)
    //* {
    //*     Serial.print("  ");
    //*     Serial.println(file.path());
    //*     file = root.openNextFile();
    //* }

    //* Setup frontend routes
    defineFrontRoutes();
    defineBackRoutes();

    server.onNotFound([](AsyncWebServerRequest *request)
                      {
        // Serial.print("404: ");
        // Serial.println(request->url());
        request->send(404, "text/plain", "Not Found"); });

    server.begin();
    Serial.println("Server started");
    debugNetworkInfo();
}

void ServerManager::debugNetworkInfo()
{
    Serial.println("\n=== DEBUG NETWORK INFO ===");

    //* Check WiFi mode
    Serial.print("WiFi Mode: ");
    switch (WiFi.getMode())
    {
    case WIFI_MODE_NULL:
        Serial.println("NULL");
        break;
    case WIFI_MODE_STA:
        Serial.println("STA");
        break;
    case WIFI_MODE_AP:
        Serial.println("AP");
        break;
    case WIFI_MODE_APSTA:
        Serial.println("AP+STA");
        break;
    }

    //* Check STA connection
    Serial.print("STA Status: ");
    switch (WiFi.status())
    {
    case WL_CONNECTED:
        Serial.println("CONNECTED");
        break;
    case WL_NO_SSID_AVAIL:
        Serial.println("NO SSID");
        break;
    case WL_CONNECT_FAILED:
        Serial.println("FAILED");
        break;
    case WL_IDLE_STATUS:
        Serial.println("IDLE");
        break;
    case WL_DISCONNECTED:
        Serial.println("DISCONNECTED");
        break;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("STA IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Gateway: ");
        Serial.println(WiFi.gatewayIP());
        Serial.print("Subnet: ");
        Serial.println(WiFi.subnetMask());
    }

    //* Check AP
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("AP Clients: ");
    Serial.println(WiFi.softAPgetStationNum());

    Serial.println("==========================\n");
}