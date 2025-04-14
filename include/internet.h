#pragma once
#include <NTPClient.h>
#include <WiFi.h>

#include "real-time-clock.h"

class Internet {
private:
  const char *ssid;
  const char *password;
  const char *ntpServer;
  const long gmtOffset;

  const bool verbose = false; // Set to true for debugging
  const int maxAttempts = 5;  // Maximum number of attempts to connect to WiFi

  WiFiUDP ntpUDP;
  NTPClient timeClient;

public:
  Internet(const char *ssid, const char *password, const char *ntpServer,
           const long gmtOffset);
  Internet(const char *ssid, const char *password, const char *ntpServer,
           const long gmtOffset, int verbose);

  void connect();
  void setTime(RealTimeClock &realTimeClock);

  bool isConnected();
};
