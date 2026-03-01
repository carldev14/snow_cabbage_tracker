#include <config/system_config.h>

void ActuatorsManager::runBuzzerPattern()
{
    // Static variables persist between calls
    static unsigned long lastRunTime = 0;
    static bool isPlaying = false;
    
    unsigned long now = millis();
    
    // If pattern is playing, update it
    if (isPlaying) {
        // Stop after 800ms
        if (now - lastRunTime >= 800) {
            digitalWrite(SystemConfig::BUZZER_PIN, LOW);
            isPlaying = false;
            Serial.println("[Buzzer] Pattern complete");
        }
        return;  // Don't restart while playing
    }
    
    // Start a new pattern (only if not playing)
    if (!isPlaying) {
        Serial.println("[Buzzer] Starting pattern");
        lastRunTime = now;
        isPlaying = true;
        
        // Play the pattern using short blocking delays
        // This is acceptable since it only runs when triggered
        digitalWrite(SystemConfig::BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(SystemConfig::BUZZER_PIN, LOW);
        delay(200);
        digitalWrite(SystemConfig::BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(SystemConfig::BUZZER_PIN, LOW);
        
        isPlaying = false;  // Pattern done
        Serial.println("[Buzzer] Pattern complete");
    }
}
