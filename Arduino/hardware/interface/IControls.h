#ifndef ICONTROLS_H
#define ICONTROLS_H

#include "IHardwareInterface.h"

class IControls
{
public:
    virtual void SetLock(HardwareState state) = 0;
    virtual void SetSoap(HardwareState state, int dispenser) = 0;
    virtual void EnableBuzzer(int timeInMs) = 0;
};

#endif
