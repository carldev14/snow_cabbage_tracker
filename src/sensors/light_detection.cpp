#include <config/system_config.h>

bool SensorsManager::isDimLightDetected()
{
    bool value;
    uint16_t raw_light = analogRead(SystemConfig::LIGHT_SENSOR);
    
    // If raw light is less than or equal to 500, we consider it dim light. This threshold can be adjusted based on testing and environment.
    if (raw_light <= 500)
    {
        value = true;
    }
    else
    {
        value = false;
    }

    return value;
}