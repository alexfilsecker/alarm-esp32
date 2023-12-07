#include <Arduino.h>

#include "buzzer.h"

Buzzer::Buzzer(int pin)
    : pin(pin)
{
}

void Buzzer::setup()
{
    pinMode(pin, OUTPUT);
}

void Buzzer::beep()
{
    digitalWrite(pin, HIGH);
}

void Buzzer::beepnt()
{
    digitalWrite(pin, LOW);
}
