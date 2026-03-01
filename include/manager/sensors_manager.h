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
    bool getSoilMoistureStatus(); //* this will trigger the water pump  

    //* Photoresistor
    bool isDimLightDetected(); //* this will trigger the led strips

    const uint16_t WET_THRESHOLD = 500; // combination threshold of three sensor
    // const uint8_t WET_THRESHOLD = 1000; // Above 70% = WET
private:
    DHT *dhtSensor;
};
