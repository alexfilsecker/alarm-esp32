#include "Alarm.h"
#include <Arduino.h>
#include <cstring>
#include <sstream>

std::string intToStr(const int number) {
  std::stringstream ss;
  if (number < 10) {
    ss << "0";
  }
  ss << number;
  return ss.str();
}

char *DayAlarm::toStr(BeginOrEnd beginOrEnd) {
  uint16_t totalMinutes;
  switch (beginOrEnd) {
  case BeginOrEnd::BEGGINING:
    totalMinutes = beginMin;
    break;
  case BeginOrEnd::ENDING:
    totalMinutes = endMin;
    break;
  }

  const int hour = totalMinutes / 60;
  const int minutes = totalMinutes % 60;

  std::string timeString = intToStr(hour) + ":" + intToStr(minutes);
  char *cstr = new char[timeString.length() + 1];
  std::strcpy(cstr, timeString.c_str());

  return cstr;
}

Alarm::Alarm() {};

Alarm::Alarm(bool verbose) : verbose(verbose) {};

void Alarm::setAlarm(const Days day, DayAlarm dayAlarm) {
  alarms[uint8_t(day)] = dayAlarm;
  if (verbose) {
    const std::string dayStr = daysStrMap[day];
    char *beginTime = dayAlarm.toStr(BeginOrEnd::BEGGINING);
    char *endTime = dayAlarm.toStr(BeginOrEnd::ENDING);
    Serial.printf("Alarm on %s set from %s to %s\n", dayStr.c_str(), beginTime,
                  endTime);
  }
}

void Alarm::setAlarms(DayAlarm dayAlarms[7]) {
  for (uint8_t i = 0; i < 7; i++) {
    setAlarm(Days(i), dayAlarms[i]);
  }
}
