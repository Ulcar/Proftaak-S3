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

    _centipede->DigitalWrite(OUTPUT_HEATER, HIGH);
}

void Heater::Set(HardwareState state)
{
    _centipede->DigitalWrite(OUTPUT_HEATER, state != STATE_ON);
}

Temperature Heater::GetTemperature()
{
    int temperature2 = _centipede->DigitalRead(INPUT_TEMPERATURE_2);
    int temperature1 = _centipede->DigitalRead(INPUT_TEMPERATURE_1);

    return (Temperature) ((temperature2 << 1) | temperature1);
}
