#include "scale.h"

Scale::Scale(int doutPin, int clkPin, long threshold)
    : doutPin(doutPin), clkPin(clkPin), threshold(threshold)
{
    read = 0;
    isOverThreshold = false;
}

void Scale::setup()
{
    scale.begin(doutPin, clkPin);
}

void Scale::update()
{
    read = scale.read();
    isOverThreshold = read > threshold;
}

void Scale::printStatus()
{
    Serial.print("Read: ");
    Serial.print(read);
    Serial.print(" | Threshold: ");
    Serial.print(threshold);
    Serial.print(" | Is over threshold: ");
    Serial.println(isOverThreshold);
}