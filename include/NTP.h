#pragma once
#include "RealTimeClock.h"
#include <NTPClient.h>
#include <WiFi.h>

class NTP {
private:
  const char *ntpServer;
  const bool verbose = false;

  unsigned long lastSyncEpochUTC = 0;
  unsigned long lastSyncMillis = 0;

  int16_t gmtOffset;

  NTPClient timeClient;
  WiFiUDP ntpUDP;

public:
  NTP(const char *ntpServer, const long gmtOffset);
  NTP(const char *ntpServer, const long gmtOffset, bool verbose);

  void setup();
  void update();

  void setGMTOffset(const int16_t gmtOffset);
  void printTime();

  void setTime(RealTimeClock &realTimeClock);

  unsigned long long getMillisUTCEpochTime();
};
