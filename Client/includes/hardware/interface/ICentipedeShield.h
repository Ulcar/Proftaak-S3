#ifndef ICENTIPEDESHIELD_H
#define ICENTIPEDESHIELD_H

class ICentipedeShield
{
public:
    virtual void Initialize() = 0;
    virtual void PinMode(int pin, int mode) = 0;
    virtual void DigitalWrite(int pin, int mode) = 0;
    virtual int DigitalRead(int pin) = 0;
};

#endif
