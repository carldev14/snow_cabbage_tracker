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

    //** SENSORS
    
    static const uint8_t SOIL_SENSOR_1 = 35;
    static const uint8_t SOIL_SENSOR_2 = 36;
    static const uint8_t SOIL_SENSOR_3 = 39;
    static const uint8_t DHT11_PIN = 19;
    static const uint8_t DHT11_TYPE = 11;

    //** ACTUATORS
    static const uint8_t BUZZER_PIN = 25;
    static const uint8_t WATER_PUMP_PIN = 23;
    static const uint8_t LED_STRIP_PIN = 18;

    //** STEPPER MOTOR
    static const uint8_t STEP_PIN = 26; // Step pin for stepper driver
    static const uint8_t DIR_PIN = 27;  // Direction pin for stepper driver
    //* SLEEP_PIN is used to control power to the stepper driver. Set HIGH to enable the driver and LOW to put it to sleep (saving power and preventing overheating when not in use).
    //* Both reset pin and sleep pin are connected together for simplicity, so we can just control the sleep pin to manage power to the driver.
    static const uint8_t SLEEP_PIN = 22;

    //** I2C
    static const uint8_t I2C_SDA = 33;
    static const uint8_t I2C_SCL = 32;

    //** ===== PIN GROUP ARRAYS =====
    static const uint8_t SOIL_SENSORS[];
    static const uint8_t NUM_SOIL_SENSORS;

    static const uint8_t ACTUATOR_PINS[];
    static const uint8_t NUM_ACTUATORS;

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