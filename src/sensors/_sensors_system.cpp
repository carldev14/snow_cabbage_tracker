#include "_sensors_manager.h"

// Constructor - initialize dhtSensor to nullptr
SensorsManager::SensorsManager() : dhtSensor(nullptr)
{
    // Constructor body - nothing needed here
}

// Destructor
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
    // Create DHT object if it doesn't exist
    if (dhtSensor == nullptr)
    {
        dhtSensor = new DHT(PinsManager::DHT11_PIN, PinsManager::DHT11_TYPE);
    }

    // Start the dht11
    dhtSensor->begin();

    // Initializes Sensors
    pinMode(PinsManager::LIGHT_SENSOR_PIN, INPUT); // Define the light sensor pin as INPUT
    pinMode(PinsManager::SOIL_SENSOR_1, INPUT);
    pinMode(PinsManager::SOIL_SENSOR_2, INPUT);
    pinMode(PinsManager::SOIL_SENSOR_3, INPUT);

    delay(2000); // DHT11 needs startup time

    Serial.println("All sensors initialized");
}




