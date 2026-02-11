#include <config/system_config.h>

float SensorsManager::getSoilMoistData(int SMNum)
{
    int pin;

    // Determine pin
    switch (SMNum) {
        case 1: pin = SystemConfig::SOIL_SENSOR_1; break;
        case 2: pin = SystemConfig::SOIL_SENSOR_2; break;
        case 3: pin = SystemConfig::SOIL_SENSOR_3; break;
        default:
            Serial.printf("[Soil] Invalid sensor: %d\n", SMNum);
            return -1.0f;
    }

    // Read with averaging to reduce noise
    int soilValue = 0;
    for (int i = 0; i < 10; i++) {
        soilValue += analogRead(pin);
        delay(2);
    }
    soilValue /= 10;

    // === CALIBRATION FOR RESISTIVE SENSORS ===
    // TYPICAL RESISTIVE SENSOR VALUES:
    // COMPLETELY DRY in air: ~4095 (max ADC, open circuit)
    // COMPLETELY WET in water: ~1500-2000 (low resistance)
    const int DRY_VALUE = 4095;   // MAXIMUM: Sensor dry in air
    const int WET_VALUE = 1800;   // ADJUST THIS: Sensor in water
    
    // Map: high ADC (dry) → 0%, low ADC (wet) → 100%
    int percentage = map(soilValue, DRY_VALUE, WET_VALUE, 0, 100);
    percentage = constrain(percentage, 0, 100);

    // Debug
    Serial.printf("[Soil%d] Raw=%d, Moist=%d%% (Dry=%d, Wet=%d)\n",
                  SMNum, soilValue, percentage, DRY_VALUE, WET_VALUE);
    
    return (float)percentage;
}
