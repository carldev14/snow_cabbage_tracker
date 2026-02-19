#include "manager/logic_manager.h"
#include "config/system_config.h"

// Pure millis timer variables
unsigned long logicTimerLast = 0;
const unsigned long LOGIC_INTERVAL = 5000UL; // 5 seconds

LogicManager::LogicManager()
{
    // Constructor implementation
}

void LogicManager::runRainSafety()
{
    uint8_t humidity = sensors.getDHTData(false);
    uint8_t tempC = sensors.getDHTData(true);

    // Serial.println("[Temp]" + tempC);
    // Serial.println("[HUmidity]" + humidity);

    if (humidity > 88.0 && tempC < 32.0)
    {
        // Serial.println("[Logic] Rain likely");
        actuators.closeCover();
        actuators.runBuzzerPattern();

    }
    else
    {
        // Serial.println("[Logic] No rain");
        actuators.openCover();
    }
}

void LogicManager::runNightMode()
{
    if (sensors.isDimLightDetected())
    {
        Serial.println("[Logic] Night detected, turning ON LED strip");
        actuators.closeCover();
        actuators.runBuzzerPattern();
        actuators.toggleArtificialLight(true);
    }
    else
    {
        Serial.println("[Logic] Day detected, turning OFF LED strip");
        actuators.openCover();
        actuators.toggleArtificialLight(false);
    }
}

void LogicManager::runSprinkler()
{
    uint16_t moist1 = sensors.getSoilMoistData(1);
    uint16_t moist2 = sensors.getSoilMoistData(2);
    uint16_t moist3 = sensors.getSoilMoistData(3);

    if (moist1 != 0 && moist2 != 0 && moist3 != 0)
    {
        uint16_t finalMoist = (moist1 + moist2 + moist3); // sum them up, then next is to compared them
        if (finalMoist < sensors.DRY_THRESHOLD)
        {
            Serial.println("[Logic] Soil is dry, turning ON water pump");
            actuators.toggleWaterPump(true);
            actuators.runBuzzerPattern();

            Serial.println("[Water pump] " + String(digitalRead(SystemConfig::WATER_PUMP_PIN)));
        }
        else
        {
            Serial.println("[Logic] Soil is moist enough, turning OFF water pump");
            actuators.toggleWaterPump(false);
            Serial.println("[Water pump] " + String(digitalRead(SystemConfig::WATER_PUMP_PIN)));
        }
    }
    else
    {
        // Serial.println("[Logic] Invalid soil moisture data");
    }
}

void LogicManager::runLogic()
{

    // if (!wifi.isTimeSynchronized)
    //     return;
    actuators.runStepper();

    // Check if 5 seconds have elapsed
    unsigned long now = millis();
    if (now - logicTimerLast >= LOGIC_INTERVAL)
    {
        logicTimerLast = now; // reset timer

        // Run logic functions
        runRainSafety();
        runSprinkler();
        runNightMode();
    }
}
