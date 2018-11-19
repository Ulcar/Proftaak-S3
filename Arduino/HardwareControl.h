#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include "hardware/interface/IHardwareInterface.h"
#include "hardware/interface/IWater.h"

#include "includes/Vector.h"

class HardwareControl
{
public:
    void AddInterface(IHardwareInterface* interface);
    IHardwareInterface* GetInterface(String name);

private:
    Vector<IHardwareInterface*> _interfaces;
};

#endif
