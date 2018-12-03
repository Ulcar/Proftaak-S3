#ifndef IWATER_H
#define IWATER_H

#include "IHardwareInterface.h"

enum WaterLevel
{
    WL_EMPTY,
    WL_25,
    WL_50,
    WL_FULL
};

class IWater
{
public:
    virtual WaterLevel GetLevel() = 0;
    virtual bool HasPressure() = 0;

    virtual void SetSink(HardwareState state) = 0;
    virtual void SetDrain(HardwareState state) = 0;
};

#endif
