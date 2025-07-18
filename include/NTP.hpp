#pragma once
#include "RealTimeClock.hpp"
#include <NTPClient.h>
#include <WiFi.h>

struct AlarmUsefulInfo {
  uint16_t localMinutes;
  uint8_t dayIndex;
};

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

  AlarmUsefulInfo getAlarmUsefulInfo();
};
