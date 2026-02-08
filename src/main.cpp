#include "Arduino.h"
#include "config/system_config.h"
#include "manager/system/wifi_manager.h"
#include "manager/logic_manager.h"

LogicManager logic;


void setup()
{
    Serial.begin(9600);
    SystemConfig::get().begin(); // Initializes the system
}

void loop()
{
    // Run Wifi updates 
    wifi.update();

    // Run main logic
    logic.runLogic();
    
}