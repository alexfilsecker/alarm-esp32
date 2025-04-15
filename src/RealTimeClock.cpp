#include "RealTimeClock.h"

RealTimeClock::RealTimeClock(int sdaPin, int sclPin)
    : sdaPin(sdaPin), sclPin(sclPin) {}

void RealTimeClock::setup() {
  Wire.begin(sdaPin, sclPin);
  rtc.begin();
}

DateTime RealTimeClock::now() { return rtc.now(); }

void RealTimeClock::setTime(DateTime time) { rtc.adjust(time); }

void RealTimeClock::printTime(DateTime time) {
  Serial.print(time.year(), DEC);
  Serial.print('/');
  Serial.print(time.month(), DEC);
  Serial.print('/');
  Serial.print(time.day(), DEC);
  Serial.print(' ');
  Serial.print(time.hour(), DEC);
  Serial.print(':');
  Serial.print(time.minute(), DEC);
  Serial.print(':');
  Serial.print(time.second(), DEC);
  Serial.println();
}

void RealTimeClock::printTime() { printTime(now()); }
