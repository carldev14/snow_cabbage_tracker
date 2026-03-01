#include <config/system_config.h>

// === FIX 1: Improved relay control with proper debouncing ===
void useRelay(int pin, bool deviceShouldBeOn, bool reverseLogic = false, String name = "")
{
    static unsigned long lastToggleTime = 0;
    static unsigned long lastDebounceTime = 0;
    unsigned long now = millis();
    
    // Apply reverse logic if needed (for active-LOW relays)
    bool actualState = reverseLogic ? !deviceShouldBeOn : deviceShouldBeOn;
    
    // Read current pin state
    int currentSignal = digitalRead(pin);
    bool currentState = (currentSignal == HIGH);
    
    // === FIX 2: Proper debounce - prevent rapid toggling ===
    if (now - lastToggleTime < 500)  // 500ms minimum between toggles
    {
        if (now - lastDebounceTime > 1000) // Print warning every second max
        {
            Serial.println("[Relay " + name + "] ⚠️ Toggle ignored - too fast (min 500ms between toggles)");
            lastDebounceTime = now;
        }
        return;
    }
    
    // Only act if state actually needs to change
    if (currentState != actualState)
    {
        digitalWrite(pin, actualState ? HIGH : LOW);
        lastToggleTime = now;
        
        Serial.print("[Relay " + name + "] ");
        Serial.print(actualState ? "ON ✓" : "OFF ✓");
        Serial.print(" (Requested: ");
        Serial.print(deviceShouldBeOn ? "ON" : "OFF");
        if (reverseLogic) Serial.print(" - reversed for active-LOW");
        Serial.println(")");
    }
    else
    {
        // Optional: Uncomment for debugging
        // Serial.println("[Relay " + name + "] Already in requested state");
    }
}

// === FIX 3: Fixed LED strip control with proper documentation ===
void ActuatorsManager::toggleArtificialLight(bool turnOn)
{
    // LED Strip uses active-LOW relay (HIGH = OFF, LOW = ON)
    // So we set reverseLogic = true
    useRelay(SystemConfig::LED_STRIP_PIN, turnOn, true, "LED_Strip");
}

// === FIX 4: Fixed water pump control ===
void ActuatorsManager::toggleWaterPump(bool turnOn)
{
    // Water pump uses active-HIGH relay (HIGH = ON, LOW = OFF)
    // So we set reverseLogic = false
    useRelay(SystemConfig::WATER_PUMP_PIN, turnOn, false, "Water_Pump");
}