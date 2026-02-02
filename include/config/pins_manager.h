#pragma once
#include <Arduino.h>


class PinsManager
{
public:
    PinsManager();
    void begin();

    // ===== STATIC PIN DEFINITIONS =====
    // SYSTEM
    static const int LED_BUILTIN = 2; // Onboard LED (GPIO 2)
    static const int BUTTON_PIN = 0;  // Manual button (with 10K pull-up)

    // SENSORS (Analog Input - ADC1, safe with WiFi)
    static const int LIGHT_SENSOR_PIN = 34; // Photoresistor (ADC1)
    static const int SOIL_SENSOR_1 = 35;    // Soil moisture 1 (ADC1)
    static const int SOIL_SENSOR_2 = 36;    // Soil moisture 2 (ADC1)
    static const int SOIL_SENSOR_3 = 39;    // Soil moisture 3 (ADC1)

    // DHT11 Sensor (Digital)
    static const int DHT11_PIN = 19;    // Temperature/Humidity
    static const int DHT11_TYPE = 11; // Temperature/Humidity

    // ACTUATORS
    static const int BUZZER_PIN = 25;     // 5V SFM-27 Active Buzzer (PWM)
    static const int WATER_PUMP_PIN = 23; // 12V Relay for water pump
    static const int LED_STRIP_PIN = 18;  // 5V relay RGB LED strip (PWM)


    // STEPPER MOTOR (Nema17 + DRV8825)
    static const int STEP_PIN = 26;   // DRV8825 STEP
    static const int DIR_PIN = 27;    // DRV8825 DIR
    static const int ENABLE_PIN = 14; // DRV8825 ENABLE (HIGH = disabled)
    static const int MS1_PIN = 5;     // Microstep resolution 1
    static const int MS2_PIN = 4;     // Microstep resolution 2
    static const int MS3_PIN = 13;    // Microstep resolution 3

    // I2C FOR DISPLAY/EXPANSION
    static const int I2C_SDA = 33; // I2C Data
    static const int I2C_SCL = 32; // I2C Clock

    // COMMUNICATION WITH CAMERA ESP32
    static const int CAMERA_TX = 16; // UART2 TX to Camera ESP32
    static const int CAMERA_RX = 17; // UART2 RX from Camera ESP32

    // RESERVED (DO NOT USE)
    // static const int RESERVED_1 = 1;        // TX0 (Serial)
    // static const int RESERVED_2 = 3;        // RX0 (Serial)
    // static const int RESERVED_3 = 6;        // FLASH (DO NOT USE!)
    // static const int RESERVED_4 = 7;        // FLASH (DO NOT USE!)
    // static const int RESERVED_5 = 8;        // FLASH (DO NOT USE!)
    // static const int RESERVED_6 = 9;        // FLASH (DO NOT USE!)
    // static const int RESERVED_7 = 10;       // FLASH (DO NOT USE!)
    // static const int RESERVED_8 = 11;       // FLASH (DO NOT USE!)

    // ===== PIN GROUPS (for easy iteration) =====
    static const int SOIL_SENSORS[];   // Array of soil sensor PinsManager
    static const int NUM_SOIL_SENSORS; // Count of soil sensors

    static const int ACTUATOR_PINS[]; // Array of actuator PinsManager
    static const int NUM_ACTUATORS;   // Count of actuators

    static const int INPUT_PINS[]; // Array of input PinsManager
    static const int NUM_INPUTS;   // Count of input PinsManager

    static const int OUTPUT_PINS[]; // Array of output PinsManager
    static const int NUM_OUTPUTS;   // Count of output PinsManager

private:
    // Pin mode tracking
    bool pinsInitialized = false;
};

// ===== CAMERA ESP32 PINS (COMMENTED - FOR SEPARATE PROJECT) =====
/*
// ESP32 #2 (CAMERA MODULE) - OV7670 Pins
#pragma once
#include <Arduino.h>

class CameraPins {
public:
    // OV7670 CONTROL PINS
    static const int CAM_SIOC = 22;        // I2C SCL
    static const int CAM_SIOD = 21;        // I2C SDA
    static const int CAM_VSYNC = 34;       // Vertical sync (INPUT ONLY)
    static const int CAM_HREF = 35;        // Horizontal reference (INPUT ONLY)
    static const int CAM_PCLK = 25;        // Pixel clock (INPUT ONLY)
    static const int CAM_XCLK = 26;        // System clock (PWM OUTPUT)
    static const int CAM_RESET = 27;       // Reset pin
    static const int CAM_PWDN = 14;        // Power down

    // OV7670 8-BIT DATA BUS
    static const int CAM_D0 = 4;
    static const int CAM_D1 = 5;
    static const int CAM_D2 = 18;
    static const int CAM_D3 = 19;
    static const int CAM_D4 = 23;
    static const int CAM_D5 = 13;
    static const int CAM_D6 = 12;
    static const int CAM_D7 = 15;

    // COMMUNICATION WITH MAIN ESP32
    static const int MAIN_TX = 16;         // UART2 TX to Main ESP32
    static const int MAIN_RX = 17;         // UART2 RX from Main ESP32

    // STATUS & DEBUG
    static const int CAM_LED = 2;          // Camera activity LED
    static const int STATUS_LED = 0;       // Optional status LED

    // ALTERNATIVE: ESP32-CAM BOARD (Much easier!)
    /*
    // AI-Thinker ESP32-CAM Pins (if using that board instead)
    static const int PWDN_GPIO_NUM = 32;
    static const int RESET_GPIO_NUM = -1;
    static const int XCLK_GPIO_NUM = 0;
    static const int SIOD_GPIO_NUM = 26;
    static const int SIOC_GPIO_NUM = 27;
    static const int Y9_GPIO_NUM = 35;
    static const int Y8_GPIO_NUM = 34;
    static const int Y7_GPIO_NUM = 39;
    static const int Y6_GPIO_NUM = 36;
    static const int Y5_GPIO_NUM = 21;
    static const int Y4_GPIO_NUM = 19;
    static const int Y3_GPIO_NUM = 18;
    static const int Y2_GPIO_NUM = 5;
    static const int VSYNC_GPIO_NUM = 25;
    static const int HREF_GPIO_NUM = 23;
    static const int PCLK_GPIO_NUM = 22;
    * /
};
*/