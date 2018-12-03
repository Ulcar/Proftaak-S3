#ifndef IHEATER_H
#define IHEATER_H

#include <Centipede.h>

#include "../Enums.h"

class IHeater
{
public:
    virtual void Initialize(Centipede centipede) = 0;

    virtual void Set(HardwareState state) = 0;
    virtual Temperature GetTemperature() = 0;

protected:
    Centipede _centipede;
};

#endif
