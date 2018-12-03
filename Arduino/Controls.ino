#include "hardware/Controls.h"

void Controls::Initialize(Centipede centipede)
{
    _centipede = centipede;

    _centipede.digitalWrite(OUTPUT_BUZZER, HIGH);
    _centipede.digitalWrite(OUTPUT_SOAP_1, LOW);
    _centipede.digitalWrite(OUTPUT_LOCK,   LOW);
}

void Controls::SetLock(HardwareState state)
{
    _centipede.digitalWrite(OUTPUT_LOCK, state == STATE_ON);
}

void Controls::SetSoap(HardwareState state, int dispenser)
{
    if (dispenser < 0 || dispenser > 2)
    {
        return;
    }

    switch (dispenser)
    {
    case 1:
        _centipede.digitalWrite(OUTPUT_SOAP_1, state == STATE_ON);
        break;

    // TODO: Fix this mess
    case 2:
        int mask = (1 << 0) - 1;

        if (state == STATE_ON)
        {
            mask |= 0x4;
        }

        _centipede.digitalWrite(1, 0x2 & 0x01);
        _centipede.digitalWrite(0, (0x2 >> 1) & 0x01);

        _centipede.digitalWrite(10, mask & 0x01);
        _centipede.digitalWrite(9, (mask >> 1) & 0x01);
        _centipede.digitalWrite(8, (mask >> 2) & 0x01);

        _centipede.digitalWrite(2, LOW);
        delay(80);
        _centipede.digitalWrite(2, HIGH);
        delay(10);
        _centipede.digitalWrite(2, LOW);
        break;
    }
}

void Controls::EnableBuzzer(int timeInMs)
{
}
