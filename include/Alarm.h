#pragma once

#include <cstdint>
#include <map>
#include <string>

enum class BeginOrEnd {
  BEGGINING,
  ENDING,
};

class DayAlarm {
private:
  uint16_t beginMin = 0;
  uint16_t endMin = 0;

public:
  DayAlarm() : beginMin(0), endMin(0) {}
  DayAlarm(uint16_t begin, uint16_t end) : beginMin(begin), endMin(end) {}

  char *toStr(BeginOrEnd beginOrEnd);

  bool isActive(uint16_t currentMinutes);
};

enum class Days {
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY,
};

class Alarm {
private:
  DayAlarm alarms[7];

  const bool verbose = false;

  std::map<Days, std::string> daysStrMap = {
      {Days::MONDAY, "MONDAY"},       {Days::TUESDAY, "TUESDAY"},
      {Days::WEDNESDAY, "WEDNESDAY"}, {Days::THURSDAY, "THURSDAY"},
      {Days::FRIDAY, "FRIDAY"},       {Days::SATURDAY, "SATURDAY"},
      {Days::SUNDAY, "SUNDAY"},
  };

public:
  Alarm();
  Alarm(bool verbose);

  void setAlarm(const Days day, const DayAlarm dayAlarm);
  void setAlarms(DayAlarm dayAlarms[7]);

  bool isActive(uint8_t dayIndex, uint16_t currentMinutes);
};
