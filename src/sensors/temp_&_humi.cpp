#include <_sensors_manager.h>

String SensorsManager::getHumi()
{

    float humidity = dhtSensor->readHumidity();
    if (isnan(humidity))
    {
        return "ERR:READ_FAIL - Temperature";
    }

    return String(humidity, 1); // 1 decimal place
}

String SensorsManager::getTemp()
{

    float temperature = dhtSensor->readTemperature();
    if (isnan(temperature))
    {
        return "ERR:READ_FAIL - Temperature";
    }

    return String(temperature, 1); // 1 decimal place
}