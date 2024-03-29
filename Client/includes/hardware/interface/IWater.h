#ifndef IWATER_H
#define IWATER_H

#include "ICentipedeShield.h"
#include "../../Enums.h"

class IWater
{
public:
    virtual ~IWater() { };

    virtual void Initialize(ICentipedeShield* centipede) = 0;

    virtual WaterLevel GetLevel() = 0;
    virtual bool HasPressure() = 0;

    virtual void SetSink(HardwareState state) = 0;
    virtual void SetDrain(HardwareState state) = 0;

    virtual HardwareState GetSinkState() = 0;
    virtual HardwareState GetDrainState() = 0;

protected:
    ICentipedeShield* _centipede;
};

#endif
