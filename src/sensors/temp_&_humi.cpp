#include <config/system_config.h>


float SensorsManager::getHumi()
{

    float humidity = dhtSensor->readHumidity();
    if (isnan(humidity))
    {
        return -1; // Return an error value
    }

    return humidity; //* 1 decimal place
}

float SensorsManager::getTemp()
{

    float temperature = dhtSensor->readTemperature();
    if (isnan(temperature))
    {
        return -1; // Return an error value
    }

    return temperature; //* 1 decimal place
}