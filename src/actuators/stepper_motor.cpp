#include "manager/actuators_manager.h"
#include "AccelStepper.h"

AccelStepper stepper(AccelStepper::DRIVER, SystemConfig::STEP_PIN, SystemConfig::DIR_PIN);
bool closingState = false;

void ActuatorsManager::stepperBegin()
{
    digitalWrite(SystemConfig::SLEEP_PIN, LOW); //* Disable the motor driver by default
    stepper.setMaxSpeed(1000);                  // Higher steps/sec since steps are smaller
    stepper.setAcceleration(400);
}

void ActuatorsManager::openCover()
{
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH); //* Enable the motor driver

    // Move 5 full revolutions (5 * 200 steps = 1000 steps)
    stepper.move(5000);
    digitalWrite(SystemConfig::SLEEP_PIN, LOW);
}

void ActuatorsManager::closeCover()
{
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH); //* Enable the motor driver

    // Move 5 revolutions in opposite direction
    stepper.move(-5000);
    digitalWrite(SystemConfig::SLEEP_PIN, LOW);
}

void ActuatorsManager::runStepper()
{
    // Non-blocking movement toward target
    stepper.run();
    stepper.runToPosition(); // Blocks until movement is complete
    delayMicroseconds(500);  // Add small delay between pulses
    stepper.stop();          // Stop the motor after reaching target
}