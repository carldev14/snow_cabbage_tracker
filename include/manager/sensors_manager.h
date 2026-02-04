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
    String getTemp();
    String getHumi();
    String getSoilMoistData(int SMNum);

    //* If rain detected
    bool isRainDetected();

    //* Photoresistor
    bool isNightDetected(); //* this will trigger the led strips

private:
    DHT *dhtSensor;

    //* //* Other sensor SystemConfig
    //* const int RAIN_SENSOR_PIN = A0;
    //* const int SOIL_SENSOR_PIN = A1;
    //* const int LDR_PIN = A2;
};
