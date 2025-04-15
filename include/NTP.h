#pragma once
#include "RealTimeClock.h"
#include <NTPClient.h>
#include <WiFi.h>

class NTP {
private:
  const char *ntpServer;

  const time_t epochTime;

  const bool verbose = false;

  NTPClient timeClient;
  WiFiUDP ntpUDP;

public:
  NTP(const char *ntpServer, const long gmtOffset);
  NTP(const char *ntpServer, const long gmtOffset, bool verbose);

  void setup();

  void setGMTOffset(const int8_t gmtHoursOffset);
  void printTime();

  void setTime(RealTimeClock &realTimeClock);
};
