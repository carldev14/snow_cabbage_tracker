#pragma once

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <config/pins_manager.h>

// Forward declaration to avoid circular dependencies
class DHT;

class SensorsManager
{
public:
    // Constructor
    SensorsManager();

    // Destructor
    ~SensorsManager();

    // Initialize the PinsManager
    void begin();

    // Dht11
    String getTemp();
    String getHumi();
    String getSoilMoistData(int SMNum);

    // If rain detected
    bool isRainDetected();

    // Photoresistor
    bool isNightDetected(); // this will trigger the led strips

private:
    DHT *dhtSensor;

    // // Other sensor PinsManager
    // const int RAIN_SENSOR_PIN = A0;
    // const int SOIL_SENSOR_PIN = A1;
    // const int LDR_PIN = A2;
};
