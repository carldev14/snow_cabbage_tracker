#include "config/system_config.h"
#include "manager/system/wifi_manager.h"
#include "manager/sensors_manager.h"

void setup()
{
    Serial.begin(9600); //* Start Serial communication
    SystemConfig::get().begin();       //* Initializes the system
    Serial.println("Waiting for all systems to initialize...");
    
    //* Small delay to ensure everything is set up
    delay(2000);

    //* Indicate initialization complete
    Serial.println("Initialization complete.");
    Serial.println("\n=== Plant Tracker ==="); //* Display in the monitor the Plant Tracker
}

void loop()
{
    //? Run the WiFi manager update
    wifi.update();
    //* String temp = sensors.getTemp();
    //* String Humi = sensors.getHumi();
    //* String moist = sensors.getSoilMoistData(1);
    //* Serial.println("moist:");
    //* Serial.println(moist);
    //* Serial.println("temp:");
    //* Serial.println(temp);
    //* Serial.println("humi:");
    //* Serial.println(Humi);
    //* bool isNight = sensors.isNightDetected();
    //* bool isRain = sensors.isRainDetected();
    //* Serial.println(isRain ? "Raining" : "Clear");
    //* Serial.println(isNight);
    //* Add your sensor reading logic here
    delay(1000);
}