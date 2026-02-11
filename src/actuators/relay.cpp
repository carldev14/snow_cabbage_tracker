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
    Serial.print("[Relay ");
    Serial.print(name);
    Serial.print("] Device ");
    Serial.println(deviceShouldBeOn ? "ON" : "OFF");
}

// TODO: you need to refractor this, allowing the transistor to control the relay instead — to save power.
// TODO: Same like the one for the water pump motor. Same logic and wires.

void ActuatorsManager::toggleArtificialLight(bool turnOn)
{
    // Get time as string and convert to integer
    const char *timeStr = wifi.getRealTime(); // Returns "HHMM" format
    int currentTime;

    // Safely convert string to integer
    if (strlen(timeStr) == 4)
    {
        currentTime = atoi(timeStr); // Converts "1830" to 1830
    }
    else
    {
        currentTime = 0; // Default if invalid
    }

    // === CORRECTED TIME LOGIC ===
    // Turn on ONLY between 18:00 (6PM) and 03:00 (3AM)
    // Special handling for overnight period
    bool shouldBeOn = false;

    if (turnOn)
    {
        if (currentTime >= 1800)
        {
            // After 6PM: always on
            shouldBeOn = true;
        }
        else if (currentTime <= 300)
        {
            // Before 3AM: also on (overnight)
            shouldBeOn = true;
        }
        // Between 3:01AM and 5:59PM: off
    }

    useRelay(SystemConfig::LED_STRIP_PIN, shouldBeOn, "Led Strip");
}

void ActuatorsManager::toggleWaterPump(bool turnOn)
{
    useRelay(SystemConfig::WATER_PUMP_PIN, turnOn, "Water Pump");
}