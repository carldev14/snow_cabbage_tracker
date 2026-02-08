#pragma once
#include <Arduino.h>
#include <config/system_config.h>

class ActuatorsManager
{
public:
    ActuatorsManager(); //* Constructor - NO return type

    //* Initialize the ActuatorsManager
    void begin();

    //* Relay
    void toggleArtificialLight(bool);
    void toggleWaterPump(bool);

    //* Buzzer
    void runBuzzerPattern();

    // TODO: Add driver for stepper motor
    //* With the stepper motor, we can control the opening and closing of a cover for the plant, which can help regulate sunlight and protect the plant from rain.
    void openCover();
    void closeCover();
    void stepperBegin();
    void stopCover();
    void runStepper(); // Call this in loop() to keep the stepper moving toward its target
};