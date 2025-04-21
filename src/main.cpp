#include <Arduino.h>

#include "Constants.h"
// #include "Scale.h"
// #include "RealTimeClock.h"
#include "Alarm.h"
#include "Buzzer.h"
#include "Internet.h"
#include "NTP.h"
#include "WebSocket.h"

// const long threshold = 1000000;

// Scale scale(DOUT_PIN, CLK_PIN, threshold);
// RealTimeClock realTimeClock(SDA_PIN, SCL_PIN);
Buzzer buzzer(BUZZER_PIN, true);
Alarm alarms(true);
Internet internet(SSID, PASSWORD, true);
NTP ntp(NTP_SERVER, GMT_OFFSET, true);
WebSocket webSocket(WEB_SOCKET_IP, WEB_SOCKET_PORT, &ntp, &alarms, true);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    continue;
  }
  Serial.println();
  Serial.println("  *********");
  Serial.println("  * ESP32 *");
  Serial.println("  *********\n\n");

  // scale.setup();
  // realTimeClock.setup();
  buzzer.setup();
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
