#include "config/system_config.h"

// Include actual headers
#include "manager/sensors_manager.h"
#include "manager/actuators_manager.h"

// Define global instances
SensorsManager sensors;
ActuatorsManager actuators;

// ✅ IMPLEMENTATION of get() method (moved from header)
SystemConfig &SystemConfig::get()
{
    static SystemConfig instance;
    return instance;
}

void SystemConfig::begin()
{

    Serial.println("[SystemConfig] Starting managers...");

    //* Each manager handles its own initialization

    actuators.begin();
    sensors.begin();

    //* Get the initial Data of DHT11 (TEMP and HUMI)
    sensors.getDHTData(false, true);
    sensors.getDHTData(true, true);

    initialized = true;

    // //? After the initializing process of managers; next initialize the diplay while provided a
    // //? elegant booting startup.
    // if (initialized)
    //     ui.initializing();

    // Serial.println("\n[SystemConfig] Delayed 1 seconds to ensure all the initialization complete.");
    // Serial.println("[SystemConfig] All managers started\n");
}