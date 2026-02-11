#include <config/system_config.h>
#include "AccelStepper.h"

Preferences prefs;

// Define your open/close positions (adjust as needed)
#define COVER_OPEN_POSITION 5000
#define COVER_CLOSED_POSITION 0

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
    prefs.begin("cover", false);

    coverState = (CoverState)prefs.getUChar("state", COVER_CLOSED);

    // Set pin modes for your driver
    pinMode(SystemConfig::STEP_PIN, OUTPUT);
    pinMode(SystemConfig::DIR_PIN, OUTPUT);
    pinMode(SystemConfig::SLEEP_PIN, OUTPUT);

    digitalWrite(SystemConfig::SLEEP_PIN, LOW); // Disable driver on startup
    stepper.setMaxSpeed(1000);                  // Steps per second
    stepper.setAcceleration(400);

    Serial.println("[Stepper Motor]" + coverState);
    
    // The condition where restored the previous state of the stepper motor
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
}

void ActuatorsManager::openCover()
{
    // Serial.println("\n[Stepper] Command: OPEN cover");
    coverTargetPosition = COVER_OPEN_POSITION;
    //? Movement will happen in updateStepper(), called from loop()
}

void ActuatorsManager::closeCover()
{
    // Serial.println("\n[Stepper] Command: CLOSE cover");
    coverTargetPosition = COVER_CLOSED_POSITION;
    //? Movement will happen in updateStepper(), called from loop()
}

//! CRITICAL: This function must be called continuously from your main loop()
void ActuatorsManager::runStepper()
{
    //? If we're not at the target position, we need to move
    if (stepper.currentPosition() != coverTargetPosition)
    {

        //? If we're not already moving, start a new move
        if (!coverIsMoving)
        {
            Serial.println("[Stepper] Starting movement...");
            digitalWrite(SystemConfig::SLEEP_PIN, HIGH); // Wake driver
            stepper.moveTo(coverTargetPosition);         // Set target
            coverIsMoving = true;
        }

        //* Keep the driver enabled and execute one step
        digitalWrite(SystemConfig::SLEEP_PIN, HIGH);
        bool stillMoving = stepper.run(); // Returns true while moving

        if (!stillMoving)
        {
            //* Movement just completed
            Serial.println("[Stepper] Move complete. Position: " + String(stepper.currentPosition()));
            digitalWrite(SystemConfig::SLEEP_PIN, LOW); // Sleep driver
            coverIsMoving = false;

            coverState = (coverTargetPosition == COVER_OPEN_POSITION)
                             ? COVER_OPEN
                             : COVER_CLOSED;

            prefs.putUChar("state", coverState);

            Serial.println("[Stepper] Move complete, state saved: " +
                           String(coverState == COVER_OPEN ? "OPEN" : "CLOSED"));
        }
    }
}
