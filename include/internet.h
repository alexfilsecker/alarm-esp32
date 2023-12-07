#pragma once
#include <WiFi.h>
#include <NTPClient.h>

#include "real-time-clock.h"

class Internet
{
private:
    const char *ssid;
    const char *password;
    const char *ntpServer;
    const long gmtOffset;

    WiFiUDP ntpUDP;
    NTPClient timeClient;

public:
    Internet(const char *ssid, const char *password, const char *ntpServer, const long gmtOffset);

    void connect();
    void setTime(RealTimeClock &realTimeClock);

    bool isConnected();
};