#include <config/system_config.h>

bool SensorsManager::isDimLightDetected()
{
    bool value;
    uint16_t raw_light = analogRead(SystemConfig::LIGHT_SENSOR);
    
    if (raw_light >= 500)
    {
        value = true;
    }
    else
    {
        value = false;
    }

    return value;
}