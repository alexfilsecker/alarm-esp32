#include "NTP.h"

NTP::NTP(const char *ntpServer, const long gmtOffset)
    : ntpServer(ntpServer), ntpUDP(), timeClient(ntpUDP, ntpServer) {}

NTP::NTP(const char *ntpServer, const long gmtOffset, const bool verbose)
    : ntpServer(ntpServer), ntpUDP(), timeClient(ntpUDP, ntpServer, gmtOffset),
      verbose(verbose) {}

void NTP::setGMTOffset(const int16_t gmtOffset) {
  this->gmtOffset = gmtOffset;
  if (verbose) {
    Serial.printf("Setting offset to %d", gmtOffset);
  }
}

void NTP::setup() {
  if (verbose) {
    Serial.println("NTP Client updating...");
  }

  bool result = timeClient.update();
  lastSyncEpochUTC = timeClient.getEpochTime();
  lastSyncMillis = millis();

  if (!result) {
    if (verbose) {
      Serial.println("Time Client update failed");
    }
    return;
  }

  if (verbose) {
    Serial.println("Time Client update successfull");
  }
}

void NTP::update() {
  if (millis() - lastSyncMillis <= 60000) {
    return;
  }

  if (!timeClient.update()) {
    Serial.println("NTP sync failed");
    return;
  }

  lastSyncEpochUTC = timeClient.getEpochTime();
  lastSyncMillis = millis();
  Serial.println("NTP sync successfull");
}

void NTP::printTime() {
  timeClient.setTimeOffset(gmtOffset);
  const String time = timeClient.getFormattedTime();
  timeClient.setTimeOffset(0);
  Serial.println(time);
}

unsigned long long NTP::getMillisUTCEpochTime() {
  return (unsigned long long)lastSyncEpochUTC * 1000 +
         (millis() - lastSyncMillis);
}

AlarmUsefulInfo NTP::getAlarmUsefulInfo() {
  timeClient.setTimeOffset(gmtOffset);
  const uint16_t minutes = timeClient.getHours() * 60 + timeClient.getMinutes();
  const uint8_t dayIndex = timeClient.getDay() - 1;
  timeClient.setTimeOffset(0);
  return AlarmUsefulInfo{minutes, dayIndex};
}

// void NTP::setTime(RealTimeClock &realTimeClock) { // Initialize and
// synchronize
//                                                   // RTC with NTP server
//   timeClient.begin();
//   bool result = timeClient.update();
//   Serial.println(result);
//   if (!result) {
//     Serial.println("Failed to update time from NTP server");
//     // ESP.restart();
//   } else {
//     Serial.println("Updated time from NTP server");
//     time_t epochTime = timeClient.getEpochTime();
//     realTimeClock.setTime(DateTime(epochTime + gmtOffset));
//   }
// }
