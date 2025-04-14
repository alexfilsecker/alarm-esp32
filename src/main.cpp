#include <Arduino.h>

#include "constants.h"
// #include "scale.h"
// #include "buzzer.h"
// #include "real-time-clock.h"
// #include "internet.h"

const long threshold = 1000000;

// Scale scale(DOUT_PIN, CLK_PIN, threshold);
// Buzzer buzzer(BUZZER_PIN, true);
// RealTimeClock realTimeClock(SDA_PIN, SCL_PIN);
// Internet internet(SSID, PASSWORD, NTP_SERVER, GMT_OFFSET);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up...");
  delay(1000);

  // scale.setup();
  // buzzer.setup();
  // realTimeClock.setup();
  // internet.connect();
  // if (internet.isConnected())
  // {
  //     internet.setTime(realTimeClock);
  // }
}

void loop() {

  // buzzer.loopTest();

  // scale.update();
  // scale.printStatus();
  delay(200);

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
