#ifndef ICONTROLS_H
#define ICONTROLS_H

#include "ICentipedeShield.h"
#include "../../Enums.h"

class IControls
{
public:
    virtual void Initialize(ICentipedeShield* centipede) = 0;

    virtual void SetLock(HardwareState state) = 0;
    virtual void SetSoap(HardwareState state, int dispenser) = 0;
    virtual void EnableBuzzer(int timeInMs) = 0;

protected:
    ICentipedeShield* _centipede;
};

#endif
