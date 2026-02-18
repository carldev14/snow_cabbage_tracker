#include "manager/logic_manager.h"
#include "config/system_config.h"
LogicManager logic;

void setup()
{
  Serial.begin(115200);
  SystemConfig::get().begin(); // Initializes the system
}

void loop()
{
    // Run main logic
    logic.runLogic();

}
