#include "manager/actuators_manager.h"
#include "config/system_config.h"

ActuatorsManager::ActuatorsManager()
{
    //* Constructor implementation
}

void ActuatorsManager::begin()
{
    //* Initialization pins
    //* For water pump and LED strip
    //* Both of them are configured with OUTPUT mode.
    //* Carrying the both aspect of using relay module.

    pinMode(SystemConfig::WATER_PUMP_PIN, OUTPUT);
    pinMode(SystemConfig::LED_STRIP_PIN, OUTPUT);

    //* For buzzer
    //* An active type buzzer, just need HIGH/LOW signal to turn on/off.
    pinMode(SystemConfig::BUZZER_PIN, OUTPUT);

    //* Motor driver pins
    pinMode(SystemConfig::STEP_PIN, OUTPUT);
}
