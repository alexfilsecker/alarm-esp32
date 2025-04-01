#include <Arduino.h>

#include "buzzer.h"

Buzzer::Buzzer(int pin)
    : pin(pin)
{
}

Buzzer::Buzzer(int pin, int verbose)
    : pin(pin), verbose(verbose)
{
}

void Buzzer::setup()
{
    pinMode(pin, OUTPUT);
    if (verbose)
    {
        Serial.print("Buzzer pin set to: ");
        Serial.println(pin);
    }
}

void Buzzer::beep()
{
    digitalWrite(pin, HIGH);
    if (verbose)
    {
        Serial.println("Buzzer beeped!");
    }
}

void Buzzer::beepnt()
{
    digitalWrite(pin, LOW);
    if (verbose)
    {
        Serial.println("Buzzer beepnt!");
    }
}

void Buzzer::loopTest()
{
    beep();
    delay(1000);
    beepnt();
    delay(1000);
}
