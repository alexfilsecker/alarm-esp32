#pragma once

#include "verbose/buzzerVerbose.h"

class Buzzer {
private:
  const int pin;
  BuzzerVerbose verbose;

public:
  Buzzer(int pin);
  Buzzer(int pin, bool verboseOn);

  void setup();

  void beep();
  void beepnt();

  void loopTest();

  void panicSound();
};
