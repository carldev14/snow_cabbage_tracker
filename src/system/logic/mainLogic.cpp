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
    //? convert the getRealTime String, into int for
    //? comparing to the time, if night or morning.
    int time = wifi.getRealTime().toInt();
    
    //? if the time is 1800 above, it means that it is night time
    //? Otherwise, it isn't.
    if (time > 1800)
    {
        Serial.println("[Logic] Night detected, turning ON LED strip");
        actuators.toggleArtificialLight(true);
        actuators.openCover();
    }
    else
    {
        Serial.println("[Logic] Day detected, turning OFF LED strip");
        actuators.toggleArtificialLight(false);
        actuators.closeCover();
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
        }
        else
        {
            Serial.println("[Logic] Soil is moist enough, turning OFF water pump");
            actuators.toggleWaterPump(false);
        }
    }
    else
    {
        Serial.println("[Logic] Invalid soil moisture data");
    }
}

void LogicManager::runLogic()
{
    // Run Wifi updates
    wifi.update();

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