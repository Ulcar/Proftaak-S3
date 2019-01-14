#include "includes/hardware/Water.h"

Water::Water()
{
    // ...
}

Water::~Water()
{
    // ...
}

void Water::Initialize(ICentipedeShield* centipede)
{
    _centipede = centipede;

    _centipede->DigitalWrite(OUTPUT_SINK, LOW);
    _centipede->DigitalWrite(OUTPUT_DRAIN, LOW);
}

WaterLevel Water::GetLevel()
{
    int water2 = _centipede->DigitalRead(INPUT_WATER_2);
    int water1 = _centipede->DigitalRead(INPUT_WATER_1);

    return (WaterLevel) ((water2 << 1) | water1);
}

bool Water::HasPressure()
{
    _centipede->DigitalWrite(3, LOW);

    return _centipede->DigitalRead(INPUT_PRESSURE) == HIGH;
}

void Water::SetSink(HardwareState state)
{
    _sinkState = state;

    _centipede->DigitalWrite(OUTPUT_SINK, state == STATE_ON);
}

void Water::SetDrain(HardwareState state)
{
    _drainState = state;

    _centipede->DigitalWrite(OUTPUT_DRAIN, state == STATE_ON);
}

HardwareState Water::GetSinkState()
{
    return _sinkState;
}

HardwareState Water::GetDrainState()
{
    return _drainState;
}
