#pragma once
#include <WiFi.h>
#include <HTTPClient.h>


class Internet
{
private:
    const char *ssid;
    const char *password;

public:
    Internet(const char *ssid, const char *password);

    void connect();

    bool isConnected();

    String httpGet(const char *url);

    String httpPost(const char *url, String data);
};