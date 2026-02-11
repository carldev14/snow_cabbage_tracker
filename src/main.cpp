#include "manager/logic_manager.h"
#include "config/system_config.h"
#include "Esp.h"
LogicManager logic;

void setup()
{
  Serial.begin(9600);
  ESP.getFreeHeap();           // show the memory usages
  SystemConfig::get().begin(); // Initializes the system
}

void loop()
{

    // Run Wifi updates
    wifi.update();

    // Run main logic
    logic.runLogic();

}
