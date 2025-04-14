#include <Arduino.h>

#include "constants.h"
// #include "scale.h"
#include "buzzer.h"
// #include "real-time-clock.h"
#include "internet.h"
#include "ntp.h"

// const long threshold = 1000000;

// Scale scale(DOUT_PIN, CLK_PIN, threshold);
Buzzer buzzer(BUZZER_PIN, true);
// RealTimeClock realTimeClock(SDA_PIN, SCL_PIN);
Internet internet(SSID, PASSWORD, true);
NTP ntp(NTP_SERVER, GMT_OFFSET, true);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting up...");

  // scale.setup();
  buzzer.setup();
  // realTimeClock.setup();
  internet.connect();
  if (internet.isConnected()) {
    ntp.setup();
  } else {
    buzzer.panicSound();
    ESP.restart();
  }
}

void loop() {

  // buzzer.loopTest();

  // scale.update();
  // scale.printStatus();
  delay(1000);
  ntp.printTime();

  // realTimeClock.printTime();

  // if (scale.isOverThreshold)
  // {
  //     buzzer.beep();
  // }
  // else
  // {
  //     buzzer.beepnt();
  // }
}
