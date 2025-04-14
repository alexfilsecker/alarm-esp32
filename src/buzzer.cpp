#include <Arduino.h>

#include "buzzer.h"

Buzzer::Buzzer(int pin)
    : pin(pin), verbose(BuzzerVerbose(pin))
{
}

Buzzer::Buzzer(int pin, bool verboseOn)
    : pin(pin), verbose(BuzzerVerbose(pin, verboseOn))
{
}


void Buzzer::setup()
{
    pinMode(pin, OUTPUT);
    verbose.setup();
}

void Buzzer::beep()
{
    digitalWrite(pin, HIGH);
    verbose.beep();
}

void Buzzer::beepnt()
{
    digitalWrite(pin, LOW);
    verbose.beepnt();
}

void Buzzer::loopTest()
{
    beep();
    delay(1000);
    beepnt();
    delay(1000);
}
