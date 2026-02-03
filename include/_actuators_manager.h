#pragma once
#include <config/pins_manager.h>
#include <Arduino.h>


class ActuatorManager
{
public:
    ActuatorManager();  // Constructor - NO return type
    
    // Initialize the ActuatorManager
    void begin();
    
    // Relay
    void useRelay(int pin, int value);
    bool safeRelayOn(int pin, bool state);
    void checkTimeouts();

    // Buzzer
    void runBuzzerPattern();
};
