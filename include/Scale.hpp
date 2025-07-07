#pragma once
#include <HX711.h>

class Scale {
private:
  HX711 scale;
  const int doutPin;
  const int clkPin;
  const long threshold;

  long read;
  time_t updatedAt;

public:
  Scale(int doutPin, int clkPin, long threshold);

  bool isOverThreshold;

  void setup();

  void update();
  void update(time_t updatedAt);

  long getRead() { return read; };

  void printStatus();
};
