#pragma once

class BuzzerVerbose {
private:
  const int pin;
  const bool verbose = false; // Set to true for debugging

public:
  BuzzerVerbose(int pin, bool verbose = false);

  void setup();
  void beep();
  void beepnt();
};
