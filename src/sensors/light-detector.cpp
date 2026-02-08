#include <manager/sensors_manager.h>
#include <config/system_config.h>

bool SensorsManager::isDimLightDetected()
{
  const int lightValue = digitalRead(SystemConfig::LIGHT_SENSOR_PIN);
    if (isnan(lightValue))
        Serial.println("ERR:READ_FAIL - isNight");
    //* HIGH = light, LOW = dark
    const bool isDark = (lightValue == HIGH);

    //* Debug
    //* Serial.print("Light sensor: ");
    //* Serial.print(lightValue);
    //* Serial.print(" -> ");
    //* Serial.println(isDark ? "NIGHT" : "DAY");

    return isDark; //* Returns true if it's night/dark
}