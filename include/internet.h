#pragma once
#include <NTPClient.h>
#include <WiFi.h>

class Internet {
private:
  const char *ssid;
  const char *password;

  const bool verbose = false; // Set to true for debugging
  const int maxAttempts = 5;  // Maximum number of attempts to connect to WiFi

public:
  Internet(const char *ssid, const char *password);
  Internet(const char *ssid, const char *password, int verbose);

  void connect();

  bool isConnected();
};
