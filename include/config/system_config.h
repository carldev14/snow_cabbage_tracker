#pragma once
#include <Arduino.h>

// Include actual manager headers for complete type
#include "manager/system/wifi_manager.h"
#include "manager/system/server_manager.h"
#include "manager/sensors_manager.h"
#include "manager/actuators_manager.h"

//* Global instance declarations
extern WiFiManager wifi;
extern ServerManager server;
extern SensorsManager sensors;
extern ActuatorsManager actuators;

class SystemConfig
{
public:
    //* Get the single instance
    static SystemConfig &get();

    //* Initialize all managers
    void begin();

    //** ===== PIN DEFINITIONS (for reference/access) =====
    //** SYSTEM
    static const int LED_BUILTIN = 2;
    static const int BUTTON_PIN = 0;

    //** SENSORS
    static const int LIGHT_SENSOR_PIN = 34;
    static const int SOIL_SENSOR_1 = 35;
    static const int SOIL_SENSOR_2 = 36;
    static const int SOIL_SENSOR_3 = 39;
    static const int DHT11_PIN = 19;
    static const int DHT11_TYPE = 11;

    //** ACTUATORS
    static const int BUZZER_PIN = 25;
    static const int WATER_PUMP_PIN = 23;
    static const int LED_STRIP_PIN = 18;

    //** STEPPER MOTOR
    static const int STEP_PIN = 26; // Step pin for stepper driver
    static const int DIR_PIN = 27;  // Direction pin for stepper driver
    //* SLEEP_PIN is used to control power to the stepper driver. Set HIGH to enable the driver and LOW to put it to sleep (saving power and preventing overheating when not in use).
    //* Both reset pin and sleep pin are connected together for simplicity, so we can just control the sleep pin to manage power to the driver.
    static const int SLEEP_PIN = 22;

    //** I2C
    static const int I2C_SDA = 33;
    static const int I2C_SCL = 32;

    //** UART FOR CAMERA
    static const int CAMERA_TX = 16;
    static const int CAMERA_RX = 17;

    //** ===== PIN GROUP ARRAYS =====
    static const int SOIL_SENSORS[];
    static const int NUM_SOIL_SENSORS;

    static const int ACTUATOR_PINS[];
    static const int NUM_ACTUATORS;

    //** ===== CONVENIENCE ACCESSORS =====
    static WiFiManager &WiFi() { return wifi; }
    static ServerManager &Server() { return server; }
    static SensorsManager &Sensors() { return sensors; }
    static ActuatorsManager &Actuators() { return actuators; }

private:
    SystemConfig() = default;
    SystemConfig(const SystemConfig &) = delete;
    SystemConfig &operator=(const SystemConfig &) = delete;

    bool initialized = false;
};