#include "manager/logic_manager.h"
#include "config/system_config.h"

CSE_MillisTimer logicTimer(2000); // 5-second timer

LogicManager::LogicManager()
{
    // Constructor implementation
}

void LogicManager::runRainSafety()
{
    float humidity = sensors.getHumi();
    float tempC = sensors.getTemp();

    // Philippine-specific thresholds (hotter climate)
    if (humidity > 88.0 && tempC < 32.0 && sensors.isDimLightDetected())
    {
        Serial.println("[Logic] Rain likely  ");
        actuators.closeCover();
    }
    else
    {
        Serial.println("[Logic] No rain  ");
        actuators.openCover();
    }
}

void LogicManager::runNightMode()
{
    // Get time as string and convert to integer
    const char *timeStr = wifi.getRealTime(); // Returns "HHMM" format
    int currentTime = 0;

    // Safely convert string to integer
    if (strlen(timeStr) == 4)
    {
        currentTime = atoi(timeStr); // Converts "1830" to 1830
    }

    // FIXED: Compare integer values, not string pointer
    Serial.printf("[TIME]: %d\n", currentTime);

    //? if the time is 1800 above, it means that it is night time
    //? Otherwise, it isn't.
    if (currentTime >= 1800) // Changed > to >= for clarity
    {
        Serial.println("[Logic] Night detected, turning ON LED strip");
        actuators.toggleArtificialLight(true);
        actuators.closeCover();
    }
    else
    {
        Serial.println("[Logic] Day detected, turning OFF LED strip");
        actuators.toggleArtificialLight(false);
        actuators.openCover();
    }
}

void LogicManager::runSprinkler()
{

    float moist1 = sensors.getSoilMoistData(1);
    float moist2 = sensors.getSoilMoistData(2);
    float moist3 = sensors.getSoilMoistData(3);

    if (moist1 >= 0 && moist2 >= 0 && moist3 >= 0)
    {
        if (moist1 < sensors.DRY_THRESHOLD || moist2 < sensors.DRY_THRESHOLD || moist3 < sensors.DRY_THRESHOLD)
        {
            Serial.println("[Logic] Soil is dry, turning ON water pump");
            actuators.toggleWaterPump(true);
            // digitalWrite(SystemConfig::WATER_PUMP_PIN, HIGH);
            Serial.println("[Water pump]" + digitalRead(SystemConfig::WATER_PUMP_PIN));
        }
        else
        {
            Serial.println("[Logic] Soil is moist enough, turning OFF water pump");
            actuators.toggleWaterPump(false);
            // digitalWrite(SystemConfig::WATER_PUMP_PIN, LOW);
            Serial.println("[Water pump]" + digitalRead(SystemConfig::WATER_PUMP_PIN));
        }
    }
    else
    {
        Serial.println("[Logic] Invalid soil moisture data");
    }
}

void LogicManager::runLogic()
{
    if (wifi.isTimeSynchronized)
    {

        actuators.runStepper();

        // Start timer on first run
        if (!logicTimer.isRunning())
        {
            logicTimer.start();
        }

        // Check if 5 seconds have elapsed
        if (logicTimer.isElapsed())
        {

            // Restart timer for next interval
            logicTimer.start();

            // Run all logic functions
            // runRainSafety();
            runSprinkler();
            runNightMode();
        }
    }
}