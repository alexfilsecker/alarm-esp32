#include "Alarm.hpp"
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

bool DayAlarm::isActive(uint16_t currentMinutes) {
  if (!enabled) {
    return false;
  }

  return currentMinutes >= beginMin & currentMinutes < endMin;
}

Alarm::Alarm() {};

Alarm::Alarm(bool verbose) : verbose(verbose) {};

void Alarm::setAlarm(const Days day, DayAlarm dayAlarm) {
  alarms[uint8_t(day)] = dayAlarm;
  if (verbose) {
    const std::string dayStr = daysStrMap[day];
    char *beginTime = dayAlarm.toStr(BeginOrEnd::BEGGINING);
    char *endTime = dayAlarm.toStr(BeginOrEnd::ENDING);

    const char *enabledStr;
    if (dayAlarm.enabled) {
      enabledStr = "";
    } else {
      enabledStr = "not ";
    }

    Serial.printf("Alarm %senabled on %s set from %s to %s\n", enabledStr,
                  dayStr.c_str(), beginTime, endTime);
  }
}

void Alarm::setAlarms(DayAlarm dayAlarms[7]) {
  for (uint8_t i = 0; i < 7; i++) {
    setAlarm(Days(i), dayAlarms[i]);
  }
}

bool Alarm::isActive(uint8_t dayIndex, uint16_t currentMinutes) {
  DayAlarm currentAlarm = alarms[dayIndex];
  return currentAlarm.isActive(currentMinutes);
}
