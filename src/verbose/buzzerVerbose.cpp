#include <Arduino.h>

#include "verbose/buzzerVerbose.h"

BuzzerVerbose::BuzzerVerbose(int pin, bool verbose)
    : pin(pin), verbose(verbose)
{
}

void BuzzerVerbose::setup()
{
    if (!verbose) return; // Skip setup if verbose is false

    Serial.print("Buzzer pin set to: ");
    Serial.println(pin);
}

void BuzzerVerbose::beep()
{
    if (!verbose) return; // Skip beep if verbose is false

    Serial.print("Buzzer beep on pin: ");
    Serial.println(pin);
}

void BuzzerVerbose::beepnt()
{
    if (!verbose) return; // Skip beepnt if verbose is false

    Serial.print("Buzzer should be off on pin: ");
    Serial.println(pin);
}