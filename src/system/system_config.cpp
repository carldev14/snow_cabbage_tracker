#include "config/system_config.h"

// Include actual headers
#include "manager/system/wifi_manager.h"
#include "manager/system/server_manager.h"
#include "manager/sensors_manager.h"
#include "manager/actuators_manager.h"

// Define global instances
WiFiManager wifi;
ServerManager server;
SensorsManager sensors;
ActuatorsManager actuators;

// ✅ IMPLEMENTATION of get() method (moved from header)
SystemConfig& SystemConfig::get()
{
    static SystemConfig instance;
    return instance;
}

void SystemConfig::begin()
{
    if (initialized) return;
    
    Serial.println("[SystemConfig] Starting managers...");
    
    // Each manager handles its own initialization
    wifi.begin();
    server.begin();
    sensors.begin();
    actuators.begin();
    
    initialized = true;
    Serial.println("[SystemConfig] All managers started");
}