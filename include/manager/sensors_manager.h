#pragma once

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

//* Forward declaration to avoid circular dependencies
class DHT;

class SensorsManager
{
public:
    //* Constructor
    SensorsManager();

    //* Destructor
    ~SensorsManager();

    //* Initialize the SystemConfig
    void begin();

    //* Dht11
    uint8_t getDHTData(const bool isTemp, const bool getInitial = false);
    uint16_t getSoilMoistData(int SMNum);

    //* Photoresistor
    bool isDimLightDetected(); //* this will trigger the led strips

    const uint8_t DRY_THRESHOLD = 30; // Below 30% = DRY
    const uint8_t WET_THRESHOLD = 70; // Above 70% = WET
private:
    DHT *dhtSensor;

    //* //* Other sensor SystemConfig
    //* const int RAIN_SENSOR_PIN = A0;
    //* const int SOIL_SENSOR_PIN = A1;
    //* const int LDR_PIN = A2;
};
