#ifndef CENTIPEDESHIELD_H
#define CENTIPEDESHIELD_H

#include <Centipede.h>
#include <Wire.h>

#include "interface/ICentipedeShield.h"

class CentipedeShield : public ICentipedeShield
{
public:
    CentipedeShield();
    ~CentipedeShield();

    void Initialize();
    void PinMode(int pin, int mode);
    void DigitalWrite(int pin, int mode);
    int DigitalRead(int pin);

private:
    Centipede _centipede;
};

#endif
