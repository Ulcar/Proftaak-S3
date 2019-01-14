#include "includes/hardware/Controls.h"

Controls::Controls()
{
    // ...
}

Controls::~Controls()
{
    // ...
}

void Controls::Initialize(ICentipedeShield* centipede)
{
    _centipede = centipede;

    _centipede->DigitalWrite(OUTPUT_BUZZER, HIGH);
    _centipede->DigitalWrite(OUTPUT_SOAP_1, LOW);
    _centipede->DigitalWrite(OUTPUT_LOCK,   LOW);
}

void Controls::SetLock(HardwareState state)
{
    _centipede->DigitalWrite(OUTPUT_LOCK, state == STATE_ON);
}

void Controls::SetSoap(HardwareState state, int dispenser)
{
    if (dispenser < 1 || dispenser > 2)
    {
        return;
    }

    switch (dispenser)
    {
    case 1:
        _centipede->DigitalWrite(OUTPUT_SOAP_1, state == STATE_ON);
        break;

    // TODO: Fix this mess
    case 2:
        int mask = (1 << 0) - 1;

        if (state == STATE_ON)
        {
            mask |= 0x4;
        }

        _centipede->DigitalWrite(1, 0x2 & 0x1);
        _centipede->DigitalWrite(0, (0x2 >> 1) & 0x1);

        _centipede->DigitalWrite(10, mask & 0x1);
        _centipede->DigitalWrite(9, (mask >> 1) & 0x1);
        _centipede->DigitalWrite(8, (mask >> 2) & 0x1);

        _centipede->DigitalWrite(2, LOW);
        delay(80);
        _centipede->DigitalWrite(2, HIGH);
        delay(10);
        _centipede->DigitalWrite(2, LOW);
        break;
    }
}

void Controls::SetBuzzer(HardwareState state)
{
    _centipede->DigitalWrite(OUTPUT_BUZZER, state == STATE_ON);
}
