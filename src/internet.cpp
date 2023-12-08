#include "internet.h"

Internet::Internet(const char *ssid, const char *password)
    : ssid(ssid), password(password)
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
        ESP.restart();
        return;
    }
    Serial.println("Connected to WiFi");
}

bool Internet::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String Internet::httpGet(const char *url)
{
    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();
    String payload = "";

    if (httpCode > 0)
    {
        payload = http.getString();
        Serial.println("HTTP GET request successful");
    }
    else
    {
        Serial.printf("HTTP GET request failed, error code: %d\n", httpCode);
    }

    http.end();
    return payload;
}

String Internet::httpPost(const char *url, String data)
{
    HTTPClient http;
    http.begin(url);
    
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(data);
    String payload = "";

    if (httpCode > 0)
    {
        payload = http.getString();
        Serial.println("HTTP POST request successful");
    }
    else
    {
        Serial.printf("HTTP POST request failed, error code: %d\n", httpCode);
    }

    http.end();
    return payload;
}