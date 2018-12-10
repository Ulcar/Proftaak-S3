#include "includes/hardware/Water.h"

void Water::Initialize(Centipede centipede)
{
    _centipede = centipede;

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
    _centipede.digitalWrite(OUTPUT_SINK, state == STATE_ON);
}

void Water::SetDrain(HardwareState state)
{
    _centipede.digitalWrite(OUTPUT_DRAIN, state == STATE_ON);
}
