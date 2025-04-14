#pragma once
#include "real-time-clock.h"
#include <NTPClient.h>
#include <WiFi.h>

class NTP {
private:
  const char *ntpServer;
  const long gmtOffset;

  const time_t epochTime;

  const bool verbose = false;

  NTPClient timeClient;
  WiFiUDP ntpUDP;

public:
  NTP(const char *ntpServer, const long gmtOffset);
  NTP(const char *ntpServer, const long gmtOffset, bool verbose);

  void setup();

  void printTime();

  void setTime(RealTimeClock &realTimeClock);
};
