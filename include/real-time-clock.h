#pragma once
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>

class RealTimeClock
{
private:
    const int sdaPin;
    const int sclPin;
    RTC_DS3231 rtc;

public:
    RealTimeClock(int sdaPin, int sclPin);

    void setup();

    DateTime now();
    void printTime(DateTime time);
    void printTime();

    void setTime(DateTime time);
};