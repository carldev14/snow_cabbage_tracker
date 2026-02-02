#include <system/server_manager.h>

// Definition of static members
const ServerManager::MimeType ServerManager::mimeTypes[] = {
    {".html", "text/html"},
    {".htm", "text/html"},
    {".js", "application/javascript"},
    {".css", "text/css"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".ico", "image/x-icon"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    {".json", "application/json"},
    {".txt", "text/plain"},
    {".pdf", "application/pdf"}};

const size_t ServerManager::mimeTypesCount =
    sizeof(ServerManager::mimeTypes) / sizeof(ServerManager::MimeType);

String ServerManager::getMimeType(const String &path)
{
    for (size_t i = 0; i < mimeTypesCount; i++)
    {
        if (path.endsWith(mimeTypes[i].extension))
        {
            return mimeTypes[i].mimeType;
        }
    }
    return "text/plain";
}