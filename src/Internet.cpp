#include "Internet.hpp"

Internet::Internet(const char *ssid, const char *password)
    : ssid(ssid), password(password) {};

Internet::Internet(const char *ssid, const char *password, int verbose)
    : ssid(ssid), password(password), verbose(verbose) {};

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
    Serial.print("Connecting to WiFi on attempt: ");
    Serial.println(attempts);
    attempts++;
  }
  if (!isConnected()) {
    Serial.println("Failed to connect to WiFi");
  }
  Serial.println("Connected to WiFi");
}

bool Internet::isConnected() { return WiFi.status() == WL_CONNECTED; }
