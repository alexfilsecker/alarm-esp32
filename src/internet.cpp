#include "internet.h"

Internet::Internet(const char *ssid, const char *password, const char *ntpServer, const long gmtOffset)
    : ssid(ssid), password(password), ntpUDP(), timeClient(ntpUDP, ntpServer), gmtOffset(gmtOffset)
{
}

void Internet::connect()
{
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 5)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        attempts++;
    }
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Failed to connect to WiFi");
        // ESP.restart();
    }
    Serial.println("Connected to WiFi");
}

bool Internet::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void Internet::setTime(RealTimeClock &realTimeClock)
{
    // Initialize and synchronize RTC with NTP server
    timeClient.begin();
    bool result = timeClient.update();
    Serial.println(result);
    if (!result)
    {
        Serial.println("Failed to update time from NTP server");
        // ESP.restart();
    }
    else
    {
        Serial.println("Updated time from NTP server");
        time_t epochTime = timeClient.getEpochTime();
        realTimeClock.setTime(DateTime(epochTime + gmtOffset));
    }
}