
#pragma once
#include "LiquidCrystal_I2C.h"

class DisplayManager
{
public:
    DisplayManager();
    void begin();
    void initializingPage();
    void showTempHumi(uint8_t temp, uint8_t humidity);
    void showSoilMoisture();
    void setText(const char *text, const char *pos); // Updated method signature
    void clear();

private:
    LiquidCrystal_I2C lcd;
    bool initializationComplete = false;
    unsigned long initStartTime = 0;
};