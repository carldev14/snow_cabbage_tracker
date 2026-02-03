#include "_actuators_manager.h"

ActuatorManager::ActuatorManager()
{
    // Constructor implementation
}

void ActuatorManager::begin()
{
    // Initialization pins
    // For water pump and LED strip
    // Both of them are configured with OUTPUT mode.
    // Carrying the both aspect of using relay module.

    pinMode(PinsManager::WATER_PUMP_PIN, OUTPUT);
    pinMode(PinsManager::LED_STRIP_PIN, OUTPUT);

    // For buzzer
    // An active type buzzer, just need HIGH/LOW signal to turn on/off.
    pinMode(PinsManager::BUZZER_PIN, OUTPUT);

    // Motor driver pins
    pinMode(PinsManager::STEP_PIN, OUTPUT);
}
