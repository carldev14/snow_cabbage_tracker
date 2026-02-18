#include "config/system_config.h"

void Display::useTextCenter(const char *string, uint8_t textSize, uint8_t positionY, uint16_t bgColor)
{
    uint16_t w = 0;
    
    // Set text size first
    tft.setTextSize(textSize);

    // Calculate text width
    tft.getTextBounds(string, 0, 0, 0, 0, w, 0 );

    // Calculate center position
    int16_t positionX = (width - w) / 2;

    // Set cursor and print
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(positionX, positionY);
    tft.println(string);
}

void Display::useLoadingView()
{
    tft.fillScreen(ST77XX_BLACK);
    useTextCenter("Switching View", 2, 60, ST77XX_BLACK);

    dotAnimation(120);
}

void Display::dotAnimation(uint8_t dotsY)
{
    // Loading animation
    int dotCount = 0;

    // Animate dots while "loading" this step
    for (int animation = 0; animation < 20; animation++)
    {
        // Create dot string
        String dots = "";
        for (int j = 0; j < dotCount; j++)
        {
            dots += ".";
        }
        useTextCenter(dots.c_str(), 2, dotsY, ST77XX_BLACK);

        // Update dot count for next frame
        dotCount = (dotCount + 1) % 4; // Cycles 0,1,2,3

        delay(100);
    }
}