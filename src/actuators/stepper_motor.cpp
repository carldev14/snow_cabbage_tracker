#include <config/system_config.h>
#include "AccelStepper.h"
#include <EEPROM.h>

// Define your open/close positions (adjust as needed)
#define COVER_OPEN_POSITION 5000
#define COVER_CLOSED_POSITION 0

// EEPROM address for storing cover state
#define COVER_STATE_ADDR 0

enum CoverState
{
    COVER_CLOSED = 0,
    COVER_OPEN = 1
};

CoverState coverState = COVER_CLOSED;

AccelStepper stepper(AccelStepper::DRIVER, SystemConfig::STEP_PIN, SystemConfig::DIR_PIN);
bool coverIsMoving = false;
long coverTargetPosition = COVER_OPEN_POSITION; // Default target

void ActuatorsManager::stepperBegin()
{
    // Initialize EEPROM (allocate enough space - 512 bytes is typical)
    EEPROM.begin();
    
    pinMode(SystemConfig::SLEEP_PIN, OUTPUT);

    // Wake up the driver in initialization
    digitalWrite(SystemConfig::SLEEP_PIN, HIGH);
    pinMode(SystemConfig::STEP_PIN, OUTPUT);
    pinMode(SystemConfig::DIR_PIN, OUTPUT);
    
    Serial.println(digitalRead(SystemConfig::SLEEP_PIN));

    // Read cover state from EEPROM
    coverState = (CoverState)EEPROM.read(COVER_STATE_ADDR);
    
    // Validate the read value (in case EEPROM was uninitialized)
    if (coverState != COVER_CLOSED && coverState != COVER_OPEN) {
        coverState = COVER_CLOSED;  // Default to closed if invalid
    }
    
    Serial.println(coverState);
    stepper.setMaxSpeed(1000); // Steps per second
    stepper.setAcceleration(400);

    Serial.println("[Stepper Motor]" + String(coverState));

    // Restore the previous state of the stepper motor
    if (coverState == COVER_OPEN)
    {
        stepper.setCurrentPosition(COVER_OPEN_POSITION);
        coverTargetPosition = COVER_OPEN_POSITION;
    }
    else
    {
        stepper.setCurrentPosition(COVER_CLOSED_POSITION);
        coverTargetPosition = COVER_CLOSED_POSITION;
    }

    Serial.println("[Stepper] Restored state: " +
                   String(coverState == COVER_OPEN ? "OPEN" : "CLOSED"));

    delay(2000);
}

void ActuatorsManager::openCover()
{
    coverTargetPosition = COVER_OPEN_POSITION;
    // Movement will happen in runStepper(), called from loop()
}

void ActuatorsManager::closeCover()
{
    coverTargetPosition = COVER_CLOSED_POSITION;
    // Movement will happen in runStepper(), called from loop()
}

// CRITICAL: This function must be called continuously from your main loop()
void ActuatorsManager::runStepper()
{
    // If we're not at the target position, we need to move
    if (stepper.currentPosition() != coverTargetPosition)
    {
        // If we're not already moving, start a new move
        if (!coverIsMoving)
        {
            digitalWrite(SystemConfig::SLEEP_PIN, HIGH);

            Serial.println("[Stepper] Starting movement...");
            stepper.moveTo(coverTargetPosition); // Set target
            coverIsMoving = true;
        }

        // Keep the driver enabled and execute one step
        bool stillMoving = stepper.run(); // Returns true while moving

        if (!stillMoving)
        {
            // Movement just completed
            digitalWrite(SystemConfig::SLEEP_PIN, LOW);

            Serial.println("[Stepper] Move complete. Position: " + String(stepper.currentPosition()));
            coverIsMoving = false;

            coverState = (coverTargetPosition == COVER_OPEN_POSITION)
                             ? COVER_OPEN
                             : COVER_CLOSED;

            // Save state to EEPROM
            EEPROM.write(COVER_STATE_ADDR, coverState);

            Serial.println("[Stepper] Move complete, state saved: " +
                           String(coverState == COVER_OPEN ? "OPEN" : "CLOSED"));
        }
    }
}
