#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include <Centipede.h>

#include "hardware/interface/IHardwareInterface.h"
#include "hardware/interface/IWater.h"

#define INPUT_TEMPERATURE_2  (18)
#define INPUT_TEMPERATURE_1  (19)

class HardwareControl
{
public:
    HardwareControl(Centipede centipede, int interfaceCount);

    void Initialize();

    void AddInterface(IHardwareInterface* interface);
    IHardwareInterface* GetInterface(String name);

private:
    Centipede _centipede;

    IHardwareInterface** _interfaces;
    int _interfaceCount;
};

#endif
