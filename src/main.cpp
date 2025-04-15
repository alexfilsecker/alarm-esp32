#include <Arduino.h>

#include "Constants.h"
// #include "Scale.h"
#include "Buzzer.h"
// #include "RealTimeClock.h"
#include "Alarm.h"
#include "Internet.h"
#include "NTP.h"
#include "WebSocket.h"

// const long threshold = 1000000;

// Scale scale(DOUT_PIN, CLK_PIN, threshold);
Buzzer buzzer(BUZZER_PIN, true);
// RealTimeClock realTimeClock(SDA_PIN, SCL_PIN);
Internet internet(SSID, PASSWORD, true);
NTP ntp(NTP_SERVER, GMT_OFFSET, true);
WebSocket webSocket(WEB_SOCKET_IP, WEB_SOCKET_PORT, &ntp, true);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting up...");

  Alarm alarm(true);

  // scale.setup();
  buzzer.setup();
  // realTimeClock.setup();
  internet.connect();
  if (!internet.isConnected()) {
    buzzer.panicSound();
    ESP.restart();
    return;
  }
  ntp.setup();
  webSocket.setup();
}

void loop() {
  webSocket.loop();

  // buzzer.loopTest();

  // scale.update();
  // scale.printStatus();

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
