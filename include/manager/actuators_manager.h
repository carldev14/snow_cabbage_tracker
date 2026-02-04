#pragma once
#include <Arduino.h>


class ActuatorsManager
{
public:
    ActuatorsManager();  //* Constructor - NO return type
    
    //* Initialize the ActuatorsManager
    void begin();
    
    //* Relay
    void useRelay(int pin, int value);
    bool safeRelayOn(int pin, bool state);
    void checkTimeouts();

    //* Buzzer
    void runBuzzerPattern();

    // TODO: Add driver for stepper motor
};
