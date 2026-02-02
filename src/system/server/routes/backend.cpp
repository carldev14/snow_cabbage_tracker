#include <system/server_manager.h>

void ServerManager::defineBackRoutes() {
    // Define all the backend routes here.
    server.on("/freeheap", HTTP_GET, [](AsyncWebServerRequest *request) {
        
        request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });
    

}