#include <config/system_config.h>

unsigned long DHTTimer = 0;
const unsigned long DHTInterval = 120000UL; // 2 minutes

static uint8_t cachedHumiValue = 0; // Cached temp
static uint8_t cachedTempValue = 0; // Cached temp

uint8_t SensorsManager::getDHTData(const bool isTemp, const bool getInitial)
{
    if (getInitial)
    {
        uint8_t temperature = dhtSensor->readTemperature();
        uint8_t humidity = dhtSensor->readHumidity();

        if (!isnan(temperature))
            cachedTempValue = temperature;

        if (!isnan(humidity))
            cachedHumiValue = humidity;
    }

    if (millis() - DHTTimer >= DHTInterval)
    {
        DHTTimer = millis();

        uint8_t temperature = dhtSensor->readTemperature();
        uint8_t humidity = dhtSensor->readHumidity();

        if (!isnan(temperature))
            cachedTempValue = temperature;

        if (!isnan(humidity))
            cachedHumiValue = humidity;
    }

    return isTemp ? cachedTempValue : cachedHumiValue;
}
