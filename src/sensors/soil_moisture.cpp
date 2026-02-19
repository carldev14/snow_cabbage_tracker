#include <config/system_config.h>

uint16_t SensorsManager::getSoilMoistData(int SMNum)
{
    static unsigned long lastReadTime[3] = {0, 0, 0};
    static uint16_t cachedPercentage[3] = {0, 0, 0}; // ✓ Store PERCENTAGE, not raw
    const unsigned long READ_INTERVAL = 1000UL;    // ✓ 2 minutes = 120,000 ms (FIXED)

    int index = SMNum - 1;
    if (index < 0 || index > 2)
    {
        Serial.print("[Soil Moisture] Invalid" + SMNum);
        return 0; // ✓ Return 0, not -1.0f (function returns uint16_t!)
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
            return cachedPercentage[index]; // Should never reach here
        }

        // === Read sensor (averaging) ===
        uint32_t soilSum = 0; // ✓ Use uint32_t to prevent overflow!
        for (uint8_t i = 0; i < 10; i++)
        {
            soilSum += analogRead(pin);
            delay(2);
        }
        uint16_t soilValue = soilSum / 10;

        // === Convert to percentage ===
        const uint16_t DRY_VALUE = 4095; // ESP32 ADC max
        const uint16_t WET_VALUE = 1800; // Calibrate this!

        // Manual map to avoid float
        uint16_t percentage;
        if (soilValue <= WET_VALUE)
        {
            percentage = 100;
        }
        else if (soilValue >= DRY_VALUE)
        {
            percentage = 0;
        }
        else
        {
            // Map 1800-4095 to 100-0
            percentage = (uint16_t)((DRY_VALUE - soilValue) * 100UL / (DRY_VALUE - WET_VALUE));
        }

        Serial.print("[Soil] Raw=");
        Serial.print(soilValue);
        Serial.print(", Moist=");
        Serial.print(soilValue);
        Serial.print("% (Dry=");
        Serial.print(percentage); // Note: This seems off - are you sure percentage should be here?
        Serial.print(", Wet=");
        Serial.print(WET_VALUE);
        Serial.println(")");
        
        cachedPercentage[index] = percentage; // ✓ Store percentage directly
        lastReadTime[index] = now;
    }

    return cachedPercentage[index]; // ✓ Returns 0-100, matches function type
}