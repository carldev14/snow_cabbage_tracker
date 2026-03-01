#include <config/system_config.h>

uint16_t SensorsManager::getSoilMoistData(int SMNum)
{
    static unsigned long lastReadTime[3] = {0, 0, 0};
    static uint16_t cachedRawValue[3] = {0, 0, 0}; // Store RAW values, not percentage
    const unsigned long READ_INTERVAL = 1000UL;    // Read every 1 second

    int index = SMNum - 1;
    if (index < 0 || index > 2)
    {
        Serial.print("[Soil Moisture] Invalid sensor: ");
        Serial.println(SMNum);
        return 0;
    }

    unsigned long now = millis();
    if (now - lastReadTime[index] >= READ_INTERVAL || lastReadTime[index] == 0)
    {
        // === Get pin ===
        uint8_t pin;
        switch (SMNum)
        {
        case 1:
            pin = SystemConfig::SOIL_SENSOR_1;
            break;
        case 2:
            pin = SystemConfig::SOIL_SENSOR_2;
            break;
        case 3:
            pin = SystemConfig::SOIL_SENSOR_3;
            break;
        default:
            return cachedRawValue[index];
        }

        // === Read sensor (averaging) ===
        uint32_t soilSum = 0;
        for (uint8_t i = 0; i < 10; i++)
        {
            soilSum += analogRead(pin);
            delay(2);
        }
        uint16_t soilValue = soilSum / 10;

        // Just print the raw value - no percentage conversion
        Serial.print("[Soil ");
        Serial.print(SMNum);
        Serial.print("] Raw=");
        Serial.println(soilValue);

        cachedRawValue[index] = soilValue; // Store raw value
        lastReadTime[index] = now;
    }

    return cachedRawValue[index]; // Returns raw ADC value (0-4095)
}

bool SensorsManager::getSoilMoistureStatus()
{
    getSoilMoistData(1); // Update cached value for sensor 1
    uint16_t moist1 = getSoilMoistData(1);

    if (moist1 == 0)
    {
        Serial.println("[Soil Moisture] Error reading sensor data");
        
        return false;
    }

    if (moist1 <= sensors.WET_THRESHOLD)
    {
        Serial.println("[Soil Moisture] Status: WET");
        return true; // Soil is wet
    }
    else
    {
        Serial.println("[Soil Moisture] Status: DRY");
        return false; // Soil is dry
    }
}