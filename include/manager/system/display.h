#pragma once
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7735
#include "Adafruit_miniTFTWing.h"

// Define the pins you used for wiring
constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 9;
constexpr uint8_t TFT_RST = 8; // You can also connect this to the Arduino's RESET pin

class Display
{
private:
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

    // Declare but don't initialize with calculations
    uint16_t width;
    uint16_t height;
    uint8_t centerX;
    uint8_t centerY;

public:
    Display(); // Constructor declaration

    void initializing(); // Loading screen method
    void dotAnimation(uint8_t dotsY);

    void soilMoistureView();
    void tempHumiView();
    void homeView();
    void calendarView();

    // UI(s)
    void useTextCenter(const char *string, uint8_t textSize, uint8_t positionY, uint16_t bgColor);
    void useLoadingView();
};