#include <config/system_config.h>

/**
 * ? Reminder to keep in mind when working with relays:
 * ? NO (Normally Closed): The relay is in its default state, and the circuit is closed (ON). Which is the current not flow in default
 * ? Additionally. NO is the one who supplies power to the device, so when the relay is activated, it will connect the power to the device and turn it ON.
 *
 * ? NC (Normally Open): The relay is in its default state, and the circuit is open (OFF). Which is the current flow in default
 * ? Additionally, NC is the one who supplies power to the device, so when the relay is activated, it will disconnect the power to the device and turn it OFF.
 *
 * ? COM (Common): The common terminal acts as the lever to switch between NO and NC.
 * ? Addition information: When you choose to connect in NC (Normally closed), provided you a default flowing current.
 *
 * ? In short, if you want to use the relay to turn ON as default, you can connect the device to NC and COM, and if you want to use the relay to turn OFF as default, you can connect the device to NO and COM.
 */

// Simple relay control with Active-LOW logic
void useRelay(int pin, int value, String name)
{
    static unsigned long lastToggleTime = 0;
    unsigned long now = millis();

    // === PROTECTION 1: DEBOUNCE (100ms) ===
    if (now - lastToggleTime < 100)
    {
        Serial.println("\n[Relay] SAFETY: Toggled too fast (min 100ms)");
        return;
    }

    // === LOGIC: Convert value to signal (Active-LOW) ===
    // value = HIGH: We want device ON -> send LOW to Active-LOW relay
    // value = LOW: We want device OFF -> send HIGH to Active-LOW relay
    bool signalToSend = (value == HIGH) ? LOW : HIGH;

    // === PROTECTION 2: CHECK CURRENT STATE ===
    int currentSignal = digitalRead(pin);
    if (currentSignal == signalToSend)
    {
        // Already in correct state
        // Serial.print(name);
        // Serial.print(" already ");
        // Serial.println(value == HIGH ? "ON" : "OFF");
        return; // CRITICAL: Stop here!
    }

    // === PROTECTION 3: ARC SUPPRESSION ===
    // Only needed when turning OFF (signal: LOW -> HIGH)
    if (currentSignal == LOW && signalToSend == HIGH)
    {
        delay(10);
    }

    // === EXECUTE ===
    digitalWrite(pin, signalToSend);
    lastToggleTime = now;

    // === LOGGING ===
    // Serial.print(name);
    // Serial.print(" -> ");
    // Serial.println(value == HIGH ? "ON" : "OFF");
}

void ActuatorsManager::toggleArtificialLight(bool turnOn)
{
    //? convert the getRealTime String, into int for
    //? comparing to the time, if night or morning.
    int time = wifi.getRealTime().toInt();

    //? Only turned on from the time it lit up (1800 => 6pm), until 300 (3 am)
    if (turnOn && (time >= 1800 || time <= 300))
    {
        useRelay(SystemConfig::LED_STRIP_PIN, HIGH, "Led Strip");
    }
    else
    {
        useRelay(SystemConfig::LED_STRIP_PIN, LOW, "Led Strip");
    }
}

void ActuatorsManager::toggleWaterPump(bool turnOn)
{
    useRelay(SystemConfig::WATER_PUMP_PIN, turnOn ? HIGH : LOW, "Water Pump");
}