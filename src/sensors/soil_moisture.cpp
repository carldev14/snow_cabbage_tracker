#include <config/system_config.h>

float SensorsManager::getSoilMoistData(int SMNum)
{
    int pin;

    //* Determine which soil sensor pin to use
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
        Serial.print("Invalid soil sensor number: ");
        Serial.println(SMNum);
    }

    //* Read the analog value
    int soilValue = analogRead(pin);

    // //* Debug output
    // Serial.print("[Soil ");
    // Serial.print(SMNum);
    // Serial.print("] Pin ");
    // Serial.print(pin);
    // Serial.print(": Raw=");
    // Serial.print(soilValue);

    //* Calibration values - ADJUST THESE FOR YOUR SENSOR!
    //* Dry in air vs submerged in water
    const int DRY_VALUE = 4095; //* Sensor dry in air (highest resistance)
    const int WET_VALUE = 1500; //* Sensor submerged in water (lowest resistance)

    //* Map to percentage (inverted: high value = dry, low value = wet)
    int percentage = map(soilValue, DRY_VALUE, WET_VALUE, 0, 100);

    //* Constrain to 0-100%
    percentage = constrain(percentage, 0, 100);

    // Serial.print(" | Moisture=");
    // Serial.print(percentage);
    // Serial.println("%");

    return percentage;
}
