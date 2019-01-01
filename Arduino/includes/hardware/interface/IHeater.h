#ifndef IHEATER_H
#define IHEATER_H

#include "ICentipedeShield.h"
#include "../../Enums.h"

class IHeater
{
public:
    virtual void Initialize(ICentipedeShield* centipede) = 0;

    virtual void Set(HardwareState state) = 0;
    virtual Temperature GetTemperature() = 0;

    virtual HardwareState GetState() = 0;

protected:
    ICentipedeShield* _centipede;
    Temperature _temp;
};

#endif
