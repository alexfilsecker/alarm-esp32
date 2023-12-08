#include <Arduino.h>

#include "constants.h"
#include "scale.h"
// #include "buzzer.h"
// #include "real-time-clock.h"
#include "internet.h"
#include <Ticker.h>

const long threshold = 1000000;

Scale scale(DOUT_PIN, CLK_PIN, threshold);
// Buzzer buzzer(BUZZER_PIN);
// RealTimeClock realTimeClock(SDA_PIN, SCL_PIN);
Internet internet(SSID, PASSWORD);

Ticker timer;


void timerCallback();

void setup()
{
    Serial.begin(9600);
    scale.setup();
    // buzzer.setup();
    // realTimeClock.setup();
    internet.connect();
    if (internet.isConnected())
    {
        // internet.setTime(realTimeClock);
        Serial.println("Connected to Internet");
    }

    timer.attach(5.0, timerCallback);
}

void loop()
{
}

void timerCallback()
{
    scale.update();
    const char *url = "http://172.20.10.2:8000/";
    String body = "{\"read\":\"" + String(scale.getRead()) + "\"}";
    Serial.println(body);
    String response = internet.httpPost(url, body);
    Serial.println("Response: " + response);
}