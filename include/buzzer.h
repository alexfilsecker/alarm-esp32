#pragma once

class Buzzer
{
private:
    const int pin;

public:
    Buzzer(int pin);

    void setup();

    void beep();
    void beepnt();
};