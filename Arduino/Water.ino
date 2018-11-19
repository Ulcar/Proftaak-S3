#include "hardware/Water.h"

Water::Water()
{
    this->_name = "water";
}

Water::~Water()
{
    // ...
}

WaterLevel Water::GetLevel()
{
    return (WaterLevel) ((_centipede.digitalRead(INPUT_WATER_2) << 1) | _centipede.digitalRead(INPUT_WATER_1));
}

bool Water::GetPressure()
{
    return true;
}
