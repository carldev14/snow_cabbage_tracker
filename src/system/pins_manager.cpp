// #include "config/pins_manager.h"

// // Initialize static arrays and counts
// const int PinsManager::SOIL_SENSORS[] = {SOIL_SENSOR_1, SOIL_SENSOR_2, SOIL_SENSOR_3};
// const int PinsManager::NUM_SOIL_SENSORS = sizeof(SOIL_SENSORS) / sizeof(SOIL_SENSORS[0]);

// const int PinsManager::ACTUATOR_PINS[] = {
//     WATER_PUMP_PIN, 
//     FAN_PIN, 
//     LED_GROW_PIN, 
//     LED_STRIP_PIN,
//     BUZZER_PIN,
//     STEP_PIN,
//     DIR_PIN,
//     ENABLE_PIN,
//     MS1_PIN,
//     MS2_PIN,
//     MS3_PIN
// };


// const int PinsManager::NUM_ACTUATORS = sizeof(ACTUATOR_PINS) / sizeof(ACTUATOR_PINS[0]);

// const int PinsManager::INPUT_PINS[] = {
//     LIGHT_SENSOR_PIN,
//     SOIL_SENSOR_1,
//     SOIL_SENSOR_2,
//     SOIL_SENSOR_3,
//     BATTERY_PIN,
//     BUTTON_PIN,
//     CAMERA_RX  // Input from camera
// };
// const int PinsManager::NUM_INPUTS = sizeof(INPUT_PINS) / sizeof(INPUT_PINS[0]);

// const int PinsManager::OUTPUT_PINS[] = {
//     LED_BUILTIN,
//     WATER_PUMP_PIN,
//     FAN_PIN,
//     LED_GROW_PIN,
//     LED_STRIP_PIN,
//     BUZZER_PIN,
//     STEP_PIN,
//     DIR_PIN,
//     ENABLE_PIN,
//     MS1_PIN,
//     MS2_PIN,
//     MS3_PIN,
//     CAMERA_TX  // Output to camera
// };
// const int PinsManager::NUM_OUTPUTS = sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]);

// PinsManager::PinsManager() {
//     // Constructor
// }

// void PinsManager::begin() {
//     if (pinsInitialized) return;
    
//     Serial.println("Initializing PinsManager...");
    
//     // Initialize all INPUT PinsManager
//     for (int i = 0; i < NUM_INPUTS; i++) {
//         pinMode(INPUT_PINS[i], INPUT);
//         Serial.printf("  INPUT Pin %d configured\n", INPUT_PINS[i]);
//     }
    
//     // Initialize all OUTPUT PinsManager
//     for (int i = 0; i < NUM_OUTPUTS; i++) {
//         pinMode(OUTPUT_PINS[i], OUTPUT);
//         digitalWrite(OUTPUT_PINS[i], LOW);  // Start LOW
//         Serial.printf("  OUTPUT Pin %d configured\n", OUTPUT_PINS[i]);
//     }
    
//     // Special pin configurations
    
//     // Button needs pull-up (if not external)
//     pinMode(BUTTON_PIN, INPUT_PULLUP);
    
//     // Setup PWM for buzzer and LEDs
//     ledcSetup(0, 2000, 8);  // Channel 0, 2kHz, 8-bit resolution
//     ledcAttachPin(BUZZER_PIN, 0);
    
//     ledcSetup(1, 5000, 8);  // Channel 1, 5kHz, 8-bit resolution
//     ledcAttachPin(LED_GROW_PIN, 1);
    
//     ledcSetup(2, 5000, 8);  // Channel 2, 5kHz, 8-bit resolution  
//     ledcAttachPin(LED_STRIP_PIN, 2);
    
//     // Initialize Serial communication with Camera ESP32
//     Serial2.begin(115200, SERIAL_8N1, CAMERA_RX, CAMERA_TX);
    
//     // Disable stepper driver on startup (HIGH = disabled)
//     digitalWrite(ENABLE_PIN, HIGH);
    
//     pinsInitialized = true;
//     Serial.println("✅ All PinsManager initialized successfully!");
// }