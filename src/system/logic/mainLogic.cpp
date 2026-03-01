#include "manager/logic_manager.h"
#include "config/system_config.h"

// Pure millis timer variables
unsigned long logicTimerLast = 0;
const unsigned long LOGIC_INTERVAL = 5000UL; // 5 seconds

LogicManager::LogicManager()
{
    // Constructor implementation
}

void LogicManager::enviromentalSafety()
{
    // Get sensor readings as float (not uint8_t)
    float humidity = sensors.getDHTData(false);  // Get humidity as float
    float tempC = sensors.getDHTData(true);       // Get temperature as float
    
    // Validate sensor readings
    if (tempC == 0.0 || humidity == 0.0 || 
        tempC > 60.0 || humidity > 100.0) {  // Invalid readings
        Serial.println("[Logic] ⚠️ Invalid sensor readings");
        return;
    }
    
    // Display current readings
    Serial.print("[Logic] Temp: ");
    Serial.print(tempC, 1);
    Serial.print("°C | Humidity: ");
    Serial.print(humidity, 1);
    Serial.println("%");
    
    // === EXTREME TEMPERATURE CHECKS ===
    
    // SUPER HOT conditions
    if (tempC > 40.0) {
        Serial.println("[Logic] 🔥 DANGER: Extreme heat detected! (" + String(tempC) + "°C)");
        actuators.runBuzzerPattern();  // Alert pattern
        // Could also trigger cooling fans or shade deployment
        actuators.toggleArtificialLight(false);  // Turn off lights to reduce heat
        return;
    }
    
    // SUPER COLD conditions
    if (tempC < 5.0) {
        Serial.println("[Logic] ❄️ WARNING: Very cold detected! (" + String(tempC) + "°C)");
        actuators.runBuzzerPattern();  // Alert pattern
        // Could trigger heating or protection measures
        return;
    }
    
    // === WEATHER PATTERNS (your original logic) ===
    
    // Rain likely (high humidity + moderate temp)
    if (humidity > 85.0 && tempC < 28.0) {
        Serial.println("[Logic] 🌧️ Rain likely (Humidity: " + String(humidity, 1) + "%)");
        actuators.runBuzzerPattern();
    }
    // Summer/Dry conditions (low humidity + warm temp)
    else if (humidity < 60.0 && tempC > 25.0) {
        Serial.println("[Logic] ☀️ Summer conditions - consider watering (Humidity: " + String(humidity, 1) + "%)");
        actuators.runBuzzerPattern();
    }
    // Normal conditions
    else {
        Serial.println("[Logic] ✅ Normal environmental conditions");
    }
}

int buzznNightOnce;

void LogicManager::runNightMode()
{

    if (sensors.isDimLightDetected())
    {

        if (buzznNightOnce == 0)
        {
            actuators.runBuzzerPattern();
            buzznNightOnce = 1;
        }

        Serial.println("[Logic] Night detected, turning ON LED strip");
        actuators.toggleArtificialLight(true);
    }
    else
    {
        buzznNightOnce = 0; // RESET buzznNightOnce to allow buzzer to trigger again when night is detected
        Serial.println("[Logic] Day detected, turning OFF LED strip");
        actuators.toggleArtificialLight(false);
    }
}

void LogicManager::runSprinkler()
{

    if (!sensors.getSoilMoistureStatus()) // If soil is dry
    {
        Serial.println("[Logic] Soil is dry, turning ON water pump");
        actuators.toggleWaterPump(true);
        Serial.println("[Water pump] " + String(digitalRead(SystemConfig::WATER_PUMP_PIN)));
        actuators.runBuzzerPattern();
    }
    else
    {
        Serial.println("[Logic] Soil is moist enough, turning OFF water pump");
        actuators.toggleWaterPump(false);
        Serial.println("[Water pump] " + String(digitalRead(SystemConfig::WATER_PUMP_PIN)));
    }
}

void LogicManager::runLogic()
{

    // Check if 5 seconds have elapsed
    unsigned long now = millis();
    if (now - logicTimerLast >= LOGIC_INTERVAL)
    {
        logicTimerLast = now; // reset timer

        Serial.println("\n[Logic] Running main logic functions...");
        Serial.println(analogRead(SystemConfig::LIGHT_SENSOR));
        Serial.println(sensors.isDimLightDetected() ? "Dim light detected" : "Bright light detected");

        display.showTempHumi(sensors.getDHTData(true), sensors.getDHTData(false)); // show in the lcd what the value

        // Run logic functions
        enviromentalSafety();
        runSprinkler();
        runNightMode();
    }
}
