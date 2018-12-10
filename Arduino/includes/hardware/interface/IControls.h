#ifndef ICONTROLS_H
#define ICONTROLS_H

#include <Centipede.h>

#include "../Enums.h"

class IControls
{
public:
    virtual void Initialize(Centipede centipede) = 0;

    virtual void SetLock(HardwareState state) = 0;
    virtual void SetSoap(HardwareState state, int dispenser) = 0;
    virtual void EnableBuzzer(int timeInMs) = 0;

protected:
    Centipede _centipede;
};

#endif
