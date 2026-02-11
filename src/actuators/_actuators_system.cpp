#include <config/system_config.h>

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

    // Initial value; to ensure that the component will not
    // Consume any power when initialization.
    digitalWrite(SystemConfig::LED_STRIP_PIN, LOW);  // OFF for Active-HIGH relay + transistor
    digitalWrite(SystemConfig::WATER_PUMP_PIN, LOW); // OFF for Active-HIGH relay + transitor

    //* For buzzer
    //* An active type buzzer, just need HIGH/LOW signal to turn on/off.
    pinMode(SystemConfig::BUZZER_PIN, OUTPUT);

    //* Motor driver pins
    pinMode(SystemConfig::STEP_PIN, OUTPUT);
    pinMode(SystemConfig::DIR_PIN, OUTPUT);
    pinMode(SystemConfig::SLEEP_PIN, OUTPUT);

    stepperBegin();
}
