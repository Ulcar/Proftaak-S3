#include "includes/hardware/Heater.h"

void Heater::Initialize(Centipede centipede)
{
    _centipede = centipede;

    _centipede.digitalWrite(OUTPUT_HEATER, HIGH);
}

void Heater::Set(HardwareState state)
{
    _centipede.digitalWrite(OUTPUT_HEATER, state != STATE_ON);
}

Temperature Heater::GetTemperature()
{
    int temperature2 = _centipede.digitalRead(INPUT_TEMPERATURE_2);
    int temperature1 = _centipede.digitalRead(INPUT_TEMPERATURE_1);

    return (Temperature) ((temperature2 << 1) | temperature1);
}
