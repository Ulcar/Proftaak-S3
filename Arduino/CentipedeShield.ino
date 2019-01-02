#include "includes/hardware/CentipedeShield.h"

CentipedeShield::CentipedeShield()
    : _centipede(Centipede())
{
    // ...
}

CentipedeShield::~CentipedeShield()
{
    // ...
}

void CentipedeShield::Initialize()
{
    Wire.begin(9600);

    _centipede.initialize();
}

void CentipedeShield::PinMode(int pin, int mode)
{
    _centipede.pinMode(pin, mode);
}

void CentipedeShield::DigitalWrite(int pin, int mode)
{
    _centipede.digitalWrite(pin, mode);
}

int CentipedeShield::DigitalRead(int pin)
{
    return _centipede.digitalRead(pin);
}
