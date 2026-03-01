#include "manager/system/display.h"
#include "config/system_config.h"

// Constructor - ONLY ONCE
DisplayManager::DisplayManager() : 
    lcd(0x27, 16, 2), 
    initializationComplete(false), 
    initStartTime(0)
{
    // Constructor implementation
}

void DisplayManager::begin()
{
    lcd.init();
    lcd.backlight();
    lcd.print("Display Ready");
    delay(1000);
    lcd.clear();
    initializingPage();
}

void DisplayManager::setText(const char* text, const char* pos)
{
    bool isTop = (strcmp(pos, "top") == 0);
    bool isBottom = (strcmp(pos, "bottom") == 0);

    if (!isTop && !isBottom)
    {
        Serial.print("[Display] Invalid position specified: ");
        Serial.println(pos);
        return;
    }

    if (isTop)
    {
        lcd.setCursor(0, 0);
    }
    else if (isBottom)
    {
        lcd.setCursor(0, 1);
    }

    lcd.print(text);
}

void DisplayManager::initializingPage()
{
    if (!initializationComplete)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Snow Cabbage");
        lcd.setCursor(0, 1);
        lcd.print("Initializing...");
        
        initStartTime = millis();
        initializationComplete = true;
    }

    if (millis() - initStartTime >= 3000)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("System Ready");
        lcd.setCursor(0, 1);
        lcd.print("Initialized ✓");
        
        delay(2000);
        lcd.clear();
        initializationComplete = false;
    }
}

void DisplayManager::showTempHumi(uint8_t temp, uint8_t humidity)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(humidity);
    lcd.print("%");
}

// FIX: Match header declaration (no parameters)
void DisplayManager::showSoilMoisture()
{
    lcd.clear();
    setText("Soil Moisture:", "top");
    
    // Get soil moisture status
    bool isWet = SystemConfig::Sensors().getSoilMoistureStatus();
    setText(isWet ? "WET ✓" : "DRY ✗", "bottom");
}

void DisplayManager::clear()
{
    lcd.clear();
}