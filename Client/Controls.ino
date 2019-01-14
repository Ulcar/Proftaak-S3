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

    // Credit: HardwareControl.ino in the ExampleProject_withTestSetup.zip file
    // from the supplied files on Canvas.
    case 2:
        // Configure the bit mask for the data pins.
        int mask = state == STATE_ON ? 0x4 : 0x0;

        // Set the group pins.
        _centipede->DigitalWrite(PIN_GROUP_1, LOW);
        _centipede->DigitalWrite(PIN_GROUP_2, HIGH);

        // Set the data pins.
        _centipede->DigitalWrite(PIN_DATA_A, mask & 0x1);
        _centipede->DigitalWrite(PIN_DATA_B, (mask >> 1) & 0x1);
        _centipede->DigitalWrite(PIN_DATA_C, (mask >> 2) & 0x1);

        // We have to quickly toggle the 'STROBE' pin, so that the changes are
        // handled by the simulation board.
        _centipede->DigitalWrite(PIN_STROBE, LOW);
        delay(80);

        _centipede->DigitalWrite(PIN_STROBE, HIGH);
        delay(10);

        _centipede->DigitalWrite(PIN_STROBE, LOW);
        break;
    }
}

void Controls::SetBuzzer(HardwareState state)
{
    _centipede->DigitalWrite(OUTPUT_BUZZER, state == STATE_ON);
}
