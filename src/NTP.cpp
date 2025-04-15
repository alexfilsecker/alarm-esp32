#include "NTP.h"

NTP::NTP(const char *ntpServer, const long gmtOffset)
    : ntpServer(ntpServer), ntpUDP(), timeClient(ntpUDP, ntpServer),
      epochTime(0) {}

NTP::NTP(const char *ntpServer, const long gmtOffset, const bool verbose)
    : ntpServer(ntpServer), ntpUDP(), timeClient(ntpUDP, ntpServer, gmtOffset),
      verbose(verbose), epochTime(0) {}

void NTP::setGMTOffset(const int8_t gmtHoursOffset) {
  const int16_t gmtOffset = gmtHoursOffset * 3600;
  timeClient.setTimeOffset(gmtOffset);
  if (verbose) {
    Serial.printf("Setting offset to %d", gmtOffset);
  }
}

void NTP::setup() {
  if (verbose) {
    Serial.println("NTP Client updating...");
  }

  bool result = timeClient.update();

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

void NTP::printTime() {
  const String time = timeClient.getFormattedTime();
  Serial.println(time);
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
