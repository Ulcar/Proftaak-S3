#include "hardware/Water.h"

Water::Water()
{
    this->_name = "water";
}

Water::~Water()
{
    // ...
}

void Water::Initialize()
{
    _centipede.digitalWrite(OUTPUT_SINK, LOW);
    _centipede.digitalWrite(OUTPUT_DRAIN, LOW);
}

WaterLevel Water::GetLevel()
{
    int water2 = _centipede.digitalRead(INPUT_WATER_2);
    int water1 = _centipede.digitalRead(INPUT_WATER_1);

    return (WaterLevel) ((water2 << 1) | water1);
}

bool Water::HasPressure()
{
    _centipede.digitalWrite(3, LOW);

    return _centipede.digitalRead(INPUT_PRESSURE) == HIGH;
}

void Water::SetSink(HardwareState state)
{
    switch (state)
    {
    case STATE_ON:
        _centipede.digitalWrite(OUTPUT_SINK, HIGH);
    break;

    case STATE_OFF:
        _centipede.digitalWrite(OUTPUT_SINK, LOW);
    break;
    }
}

void Water::SetDrain(HardwareState state)
{
    switch (state)
    {
    case STATE_ON:
        _centipede.digitalWrite(OUTPUT_DRAIN, HIGH);
    break;

    case STATE_OFF:
        _centipede.digitalWrite(OUTPUT_DRAIN, LOW);
    break;
    }
}
