#pragma once

class InternetVerbose
{
private:
    const char* ssid;
    const char* password;
    const char* host;
    const int port;
    const bool verbose = false; // Set to true for debugging
};