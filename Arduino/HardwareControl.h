#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include <Centipede.h>

#include "hardware/interface/IHardwareInterface.h"
#include "hardware/interface/IWater.h"

#include "includes/Vector.h"

class HardwareControl
{
public:
    HardwareControl(Centipede centipede);

    void Initialize();

    void AddInterface(IHardwareInterface* interface);
    IHardwareInterface* GetInterface(String name);

private:
    Vector<IHardwareInterface*> _interfaces;
    Centipede _centipede;
};

#endif
