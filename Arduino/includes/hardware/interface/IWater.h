#ifndef IWATER_H
#define IWATER_H

#include <Centipede.h>

#include "../../Enums.h"

class IWater
{
public:
    virtual void Initialize(Centipede centipede) = 0;

    virtual WaterLevel GetLevel() = 0;
    virtual bool HasPressure() = 0;

    virtual void SetSink(HardwareState state) = 0;
    virtual void SetDrain(HardwareState state) = 0;

protected:
    Centipede _centipede;
};

#endif
