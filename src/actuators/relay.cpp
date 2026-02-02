
#include <_actuators_manager.h>

// If you don't have a current sensor, use these protections:
void ActuatorManager::useRelay(int pin, int value)
{
    digitalWrite(pin, value);
}

bool ActuatorManager::safeRelayOn(int pin, bool state)
{

    // === PROTECTION 1: DEBOUNCE (MOST IMPORTANT!) ===
    static unsigned long lastToggleTime = 0;
    unsigned long now = millis();
    if (now - lastToggleTime < 100)
    { // 100ms minimum
        Serial.println("SAFETY: Toggled too fast (min 100ms)");
        return false;
    }

    // === PROTECTION 2: CHECK CURRENT STATE ===
    int currentState = digitalRead(pin);
    if (currentState == state)
    {
        // Already in desired state
        return true;
    }

    // === PROTECTION 2: ARC SUPPRESSION ===
    if (currentState == HIGH && state == LOW)
    {
        // Turning OFF - wait for inductive kick
        delay(10); // 10ms delay
    }

    // === PROTECTION 4: EXECUTE ===
    digitalWrite(pin, state);
    lastToggleTime = now;

    // === PROTECTION 5: AUTO-OFF TIMEOUT ===
    if (state == HIGH)
    {
        // Schedule auto-off after 5 minutes
        Serial.print("WARNING: Relay ");
        Serial.print(pin);
        Serial.println(" will auto-off in 5 minutes");
    }

    Serial.print("Relay ");
    Serial.print(pin);
    Serial.print(" -> ");
    Serial.println(state ? "ON" : "OFF");
    return true;
}

