#include <Arduino.h>
#include <WiFi.h>
#include "system/wifi_manager.h"
#include "system/server_manager.h"
// #include "config/pins_manager.h"
#include "_sensors_manager.h"

// Create instances
WiFiManager wifi;
ServerManager server;
// PinsManager PinsManager;
SensorsManager sensors;
void initializeSystem()
{
    // Initialize WiFi, Server, and Pins
    wifi.begin();
    server.begin();
    sensors.begin();
    // Display initialization completed
    Serial.println("System Initialized.");
}

void setup()
{
    delay(1000);
    Serial.begin(9600);                               // Add baud rate
    Serial.println("\n=== Snow Cabbage Tracker ==="); // Display in the monitor the Plant Tracker
    initializeSystem();                               // run initialization
}

void loop()
{
    wifi.update();
    // String temp = sensors.getTemp();
    // String Humi = sensors.getHumi();
    // String moist = sensors.getSoilMoistData(1);
    // Serial.println("moist:");
    // Serial.println(moist);
    // Serial.println("temp:");
    // Serial.println(temp);
    // Serial.println("humi:");
    // Serial.println(Humi);
    // bool isNight = sensors.isNightDetected();
    // bool isRain = sensors.isRainDetected();
    // Serial.println(isRain ? "Raining" : "Clear");
    // Serial.println(isNight);
    // Add your sensor reading logic here
    delay(1000);
}