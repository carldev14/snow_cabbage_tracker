#include <config/system_config.h>


void ServerManager::defineFrontRoutes()
{
    serveFile("/htmx.js", "/frontend/scripts/htmx.js");
    serveFile("/tailwind.js", "/frontend/scripts/tailwind.js");

    serveFile("/", "/frontend/pages/home.html");

}
