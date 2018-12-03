#ifndef IHEATER_H
#define IHEATER_H

#include "IHardwareInterface.h"

enum Temperature
{
    TEMP_OFF,
    TEMP_COLD,
    TEMP_MEDIUM,
    TEMP_HOT
};

enum HeaterState
{
    HEATER_ON,
    HEATER_OFF
};

class IHeater
{
public:
    virtual void Set(HardwareState state) = 0;
    virtual Temperature GetTemperature() = 0;
};

#endif
