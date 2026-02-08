#include <manager/sensors_manager.h>
#include <manager/actuators_manager.h>
#include <config/system_config.h>
#include <CSE_MillisTimer.h>

// ? This is all-in-one header for managing all actuators in the system, including the stepper motor, relay, and buzzer.
// ? The logic manager is the main brain of the system, responsible for making decisions based on sensor data and controlling the actuators accordingly.
// ? Wherein, it will use the datasets from the sensors manager to make decisions and then call the actuators manager to perform actions like watering the plant, turning on the LED strip, or activating the motor to open/close the cover.

class LogicManager
{
public:
    LogicManager(); //* Constructor - NO return type

    void runLogic();

private:
    void runRainSafety(); // run if rain is likely to protect the plant (close cover, turn on LED strip, etc.)
    void runNightMode();  // run if it's night to turn on the LED strip
    void runSprinkler();  // run the water pump if soil is dry
};