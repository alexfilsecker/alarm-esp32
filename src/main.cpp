#include <Arduino.h>

#include "Alarm.h"
#include "Buzzer.h"
#include "Constants.h"
#include "Internet.h"
#include "NTP.h"
#include "Scale.h"
#include "WebSocket.h"

Scale scale(DOUT_PIN, CLK_PIN, THRESHOLD);
Buzzer buzzer(BUZZER_PIN);
Alarm alarms(true);
Internet internet(SSID, PASSWORD, true);
NTP ntp(NTP_SERVER, GMT_OFFSET, true);
WebSocket webSocket(WEB_SOCKET_IP, WEB_SOCKET_PORT, &ntp, &alarms, true);

unsigned long long lastSendRead = 0;
long accumulatedRead = 0;
uint8_t readCount = 0;

void setup() {
  Serial.begin(115200);
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

  // Send read or accumulate it
  if (millisEpochTime - SEND_READ_PERIOD > lastSendRead && readCount > 0) {
    const long avgRead = accumulatedRead / readCount;
    webSocket.sendScaleRead(avgRead, millisEpochTime);
    lastSendRead = millisEpochTime;
    accumulatedRead = 0;
    readCount = 0;
  } else {
    accumulatedRead += read;
    readCount += 1;
  }

  AlarmUsefulInfo info = ntp.getAlarmUsefulInfo();
  bool alarmActive = alarms.isActive(info.dayIndex, info.localMinutes);
  bool scaleActive = scale.isOverThreshold;

  if (webSocket.forceBeep) {
    buzzer.beep();
  } else {
    if (alarmActive & scaleActive) {
      buzzer.beep();
    } else {
      buzzer.beepnt();
    }
  }
}
