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
    actuators.begin();
    sensors.begin();
    wifi.begin();
    server.begin();
    
    initialized = true;
    Serial.println("\n[SystemConfig] Delayed 5 seconds to ensure all the initialization complete.");
    delay(2000);
    Serial.println("[SystemConfig] All managers started\n");
}