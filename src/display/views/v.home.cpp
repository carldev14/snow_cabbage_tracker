#include "config/system_config.h"
void homeButton()
{
}
void Display::homeView()
{
    tft.fillScreen(ST77XX_BLACK); // use to remove the loading View, by replacing the view.
    useTextCenter("Welcome Kafarm", 2, 20, ST77XX_BLACK);
}
