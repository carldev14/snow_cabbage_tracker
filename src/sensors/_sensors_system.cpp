#include "manager/sensors_manager.h"
#include "config/system_config.h"

//* Constructor - initialize dhtSensor to nullptr
SensorsManager::SensorsManager() : dhtSensor(nullptr)
{
    //* Constructor body - nothing needed here
}

//* Destructor
SensorsManager::~SensorsManager()
{
    if (dhtSensor)
    {
        delete dhtSensor;
        dhtSensor = nullptr;
    }
}

void SensorsManager::begin()
{
    //* Create DHT object if it doesn't exist
    if (dhtSensor == nullptr)
    {
        dhtSensor = new DHT(SystemConfig::DHT11_PIN, SystemConfig::DHT11_TYPE);
    }

    //* Start the dht11
    dhtSensor->begin();

    //* Initializes Sensors
    pinMode(SystemConfig::LIGHT_SENSOR_PIN, INPUT); //* Define the light sensor pin as INPUT
    pinMode(SystemConfig::SOIL_SENSOR_1, INPUT);
    pinMode(SystemConfig::SOIL_SENSOR_2, INPUT);
    pinMode(SystemConfig::SOIL_SENSOR_3, INPUT);

    delay(2000); //* DHT11 needs startup time

    Serial.println("All sensors initialized");
}




