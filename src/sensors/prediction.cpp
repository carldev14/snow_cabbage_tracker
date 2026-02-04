#include <manager/sensors_manager.h>
#include <config/system_config.h>

bool SensorsManager::isRainDetected()
{
    float humidity = getHumi().toFloat();
    float tempC = getTemp().toFloat();

    //* Philippine-specific thresholds (hotter climate)

    //* Afternoon showers: High humidity after hot morning
    if (humidity > 88.0 && tempC < 32.0)
    {
        return true; //* Very likely to rain
    }

    //* General rain condition for tropics
    float dewPointDiff = ((100.0 - humidity) / 5.0);
    return (dewPointDiff < 3.0); //* More lenient for tropics
}

bool SensorsManager::isNightDetected()
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
