#include <Arduino.h>

#include "Alarm.h"
#include "Buzzer.h"
#include "Constants.h"
#include "Internet.h"
#include "NTP.h"
#include "Scale.h"
#include "WebSocket.h"

const long threshold = 1000000;

Scale scale(DOUT_PIN, CLK_PIN, threshold);
Buzzer buzzer(BUZZER_PIN, true);
Alarm alarms(true);
Internet internet(SSID, PASSWORD, true);
NTP ntp(NTP_SERVER, GMT_OFFSET, true);
WebSocket webSocket(WEB_SOCKET_IP, WEB_SOCKET_PORT, &ntp, &alarms, true);

time_t lastSendRead = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    continue;
  }
  Serial.println();
  Serial.println("  *********");
  Serial.println("  * ESP32 *");
  Serial.println("  *********\n\n");

  scale.setup();
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
  const unsigned long long millisEpochTime = ntp.getMillisUTCEpochTime();
  scale.update();
  const long read = scale.getRead();
  ntp.update();
  if (millis() - lastSendRead > 1000) {
    webSocket.sendScaleRead(read, millisEpochTime);
    lastSendRead = millis();
  }
}
