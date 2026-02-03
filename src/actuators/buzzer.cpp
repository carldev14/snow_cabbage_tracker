#include <__actuators_manager.h>

void ActuatorManager::runBuzzerPattern()
{
    // Use the built-in tone function to generate a sound on the buzzer pin
    // This can be use for warning patterns.
    // By producing alternate high and low signals with delays.
    // For additional information: This buzzer are active type.

    digitalWrite(PinsManager::BUZZER_PIN, HIGH);
    delay(2000); // Keep buzzer on for 1 second

    digitalWrite(PinsManager::BUZZER_PIN, LOW);
    delay(2000); // Keep buzzer off for 1 second

    digitalWrite(PinsManager::BUZZER_PIN, HIGH);
    delay(2000); // Keep buzzer off for 1 second

    digitalWrite(PinsManager::BUZZER_PIN, LOW);
    delay(2000); // Keep buzzer off for 1 second
}
