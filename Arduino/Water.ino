#include "hardware/Water.h"

Water::Water()
{
    this->_name = "water";
}

Water::~Water()
{
    // ...
}

int Water::GetLevel()
{
    return 5;
}

bool Water::GetPressure()
{
    return true;
}
