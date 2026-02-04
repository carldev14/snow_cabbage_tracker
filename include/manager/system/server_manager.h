#pragma once
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

class ServerManager
{
public:
    //* Constructor
    ServerManager();

    //* Initialize the server
    void begin();

    //* Update function to be called in the main loop
    void update();

    //* Mount Frontend
    void serveFile(String urlPath, String filePath);
    String getMimeType(const String &path);
    
    //* Define list of each routes
    void defineFrontRoutes(); //* front
    void defineBackRoutes();  //* back
    void debugNetworkInfo();

private:
    AsyncWebServer server;
    struct MimeType
    {
        const char *extension;
        const char *mimeType;
    };

    static const MimeType mimeTypes[]; //* Declaration
    static const size_t mimeTypesCount;
};