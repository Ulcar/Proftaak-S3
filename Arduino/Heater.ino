#include "hardware/Heater.h"

Heater::Heater()
{
    this->_name = "heater";
}

Heater::~Heater()
{
    // ...
}

void Heater::Initialize()
{
    _centipede.digitalWrite(OUTPUT_HEATER, HIGH);
}

void Heater::Set(HardwareState state)
{
    switch (state)
    {
    case STATE_ON:
        _centipede.digitalWrite(OUTPUT_HEATER, LOW);
    break;

    case STATE_OFF:
        _centipede.digitalWrite(OUTPUT_HEATER, HIGH);
    break;
    }
}

Temperature Heater::GetTemperature()
{
    int temperature2 = _centipede.digitalRead(INPUT_TEMPERATURE_2);
    int temperature1 = _centipede.digitalRead(INPUT_TEMPERATURE_1);

    return (Temperature) ((temperature2 << 1) | temperature1);
}
