#pragma once

class Buzzer
{
private:
    const int pin;
    const bool verbose = false; // Set to true for debugging

public:
    Buzzer(int pin);
    Buzzer(int pin, int verbose);

    void setup();

    void beep();
    void beepnt();

    void loopTest();
};