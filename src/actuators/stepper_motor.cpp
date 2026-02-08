#include "manager/actuators_manager.h"
#include "AccelStepper.h"

AccelStepper stepper(AccelStepper::DRIVER, SystemConfig::STEP_PIN, SystemConfig::DIR_PIN);
bool closingState = false;

void ActuatorsManager::stepperBegin()
{
    digitalWrite(SystemConfig::SLEEP_PIN, LOW); //* Disable the motor driver by default
    stepper.setMaxSpeed(1000);                   // Higher steps/sec since steps are smaller
    stepper.setAcceleration(400);
}

void ActuatorsManager::openCover()
{
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH); //* Enable the motor driver
    stepper.move(5000);
    // DON'T set to LOW here - keep it enabled for runStepper()
}

void ActuatorsManager::closeCover()
{
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH); //* Enable the motor driver
    stepper.move(-5000);
    // DON'T set to LOW here - keep it enabled for runStepper()
}

void ActuatorsManager::runStepper()
{
    // Keep SLEEP_PIN HIGH during movement
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH);
    
    // Non-blocking movement toward target
    stepper.run();
    stepper.runToPosition(); // Blocks until movement is complete
    
    // Only disable after movement is complete
    digitalWrite(SystemConfig::SLEEP_PIN, LOW);
    
    delayMicroseconds(500);  // Add small delay between pulses
    stepper.stop();          // Stop the motor after reaching target
}