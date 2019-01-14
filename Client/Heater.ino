#include "includes/hardware/Heater.h"

Heater::Heater()
{
    // ...
}

Heater::~Heater()
{
    // ...
}

void Heater::Initialize(ICentipedeShield* centipede)
{
    _centipede = centipede;
    _state = STATE_OFF;

    // Due to the way the Centipede shield works, we have to set the HEATER pin
    // to 'HIGH' in order to turn it off. And 'LOW' to turn it on.
    _centipede->DigitalWrite(OUTPUT_HEATER, HIGH);
}

void Heater::Set(HardwareState state)
{
    _state = state;

    _centipede->DigitalWrite(OUTPUT_HEATER, state != STATE_ON);
}

Temperature Heater::GetTemperature()
{
    int temperature2 = _centipede->DigitalRead(INPUT_TEMPERATURE_2);
    int temperature1 = _centipede->DigitalRead(INPUT_TEMPERATURE_1);

    return (Temperature) ((temperature2 << 1) | temperature1);
}

HardwareState Heater::GetState()
{
    return _state;
}
