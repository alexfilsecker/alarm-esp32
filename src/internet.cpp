#include "internet.h"

Internet::Internet(const char *ssid, const char *password,
                   const char *ntpServer, const long gmtOffset)
    : ssid(ssid), password(password), ntpUDP(), timeClient(ntpUDP, ntpServer),
      gmtOffset(gmtOffset) {}

Internet::Internet(const char *ssid, const char *password,
                   const char *ntpServer, const long gmtOffset, int verbose)
    : ssid(ssid), password(password), ntpUDP(), timeClient(ntpUDP, ntpServer),
      gmtOffset(gmtOffset), verbose(verbose) {}

void Internet::connect() {
  WiFi.begin(ssid, password);
  int attempts = 0;

  if (verbose) {
    Serial.print("Connecting to WiFi: ");
    Serial.print(ssid);
    Serial.print(" with password: ");
    Serial.println(password);
  }

  while (!isConnected() && attempts < 5) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    attempts++;
  }
  if (!isConnected()) {
    Serial.println("Failed to connect to WiFi");
    ESP.restart();
  }
  Serial.println("Connected to WiFi");
}

bool Internet::isConnected() { return WiFi.status() == WL_CONNECTED; }

void Internet::setTime(RealTimeClock &realTimeClock) {
  // Initialize and synchronize RTC with NTP server
  timeClient.begin();
  bool result = timeClient.update();
  Serial.println(result);
  if (!result) {
    Serial.println("Failed to update time from NTP server");
    // ESP.restart();
  } else {
    Serial.println("Updated time from NTP server");
    time_t epochTime = timeClient.getEpochTime();
    realTimeClock.setTime(DateTime(epochTime + gmtOffset));
  }
}
