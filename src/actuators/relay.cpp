#include <config/system_config.h>

// Simple relay control with Active-LOW logic
void useRelay(int pin, bool deviceShouldBeOn, String name)
{
    static unsigned long lastToggleTime = 0;
    unsigned long now = millis();

    // === PROTECTION 1: DEBOUNCE (100ms) ===
    if (now - lastToggleTime < 100)
    {
        Serial.println("\n[Relay " + name + " SAFETY]: Toggled too fast (min 100ms)");
        return;
    }

    // === LOGIC: Convert desired device state to signal ===
    // For Active-LOW relay (common type):
    // - Device ON  -> Send LOW signal
    // - Device OFF -> Send HIGH signal
    // For relay with transistor (Active-High):
    // - Device ON  -> Send HIGH signal
    // - Device OFF -> Send LOW signal
    int signalToSend;

    // Relay with external transistor (Active-High)
    signalToSend = deviceShouldBeOn ? HIGH : LOW;

    // === PROTECTION 2: CHECK CURRENT STATE ===
    int currentSignal = digitalRead(pin);
    if (currentSignal == signalToSend)
    {
        // Already in correct state
        return; // CRITICAL: Stop here!
    }

    // === EXECUTE ===
    digitalWrite(pin, signalToSend);
    lastToggleTime = now;

    // === LOGGING ===
    // Serial.print("[Relay ");
    // Serial.print(name);
    // Serial.print("] Device ");
    Serial.println(deviceShouldBeOn ? "ON" : "OFF");
}

// TODO: you need to refractor this, allowing the transistor to control the relay instead — to save power.
// TODO: Same like the one for the water pump motor. Same logic and wires.

void ActuatorsManager::toggleArtificialLight(bool turnOn)
{

    useRelay(SystemConfig::LED_STRIP_PIN, turnOn, "Led Strip");
}

void ActuatorsManager::toggleWaterPump(bool turnOn)
{
    useRelay(SystemConfig::WATER_PUMP_PIN, turnOn, "Water Pump");
}