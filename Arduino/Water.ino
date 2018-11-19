#include "hardware/Water.h"

Water::Water()
{
    // ...
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

String Water::GetName()
{
    return "water";
}
