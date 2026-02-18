#include "config/system_config.h"

Display::Display()
{
    // Initialize in constructor
    width = 320;
    height = 240;
    centerX = width / 2;  // 160
    centerY = height / 2; // 120
}

void Display::initializing()
{
    tft.init(320, 240);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);

    // Draw static elements
    useTextCenter("Plant Monitoring", 2, 46, ST77XX_BLACK);

    int statusY = 80;
    int dotsY = 110;

    const char *initSteps[] = {
        "Wifi Initialized",
        "Server Initialized",
        "Actuators Initialized",
        "Sensor Initialized"};
    int numSteps = 4;

    useTextCenter("Booting...", 1, statusY, ST77XX_BLACK);

    // Loop through each step
    for (int step = 0; step < numSteps; step++)
    {
        // Update status text
        useTextCenter(initSteps[step], 1, statusY, ST77XX_BLACK);

        // use animation loading dot
        dotAnimation(dotsY);
    }

    useTextCenter("All Initialized!", 1, statusY, ST77XX_BLACK);
    delay(500);

    
    //* Display [Loading Screen] before proceeding to the view, for better transition.
    useLoadingView();
    
    // Display Home View
    homeView();
}
