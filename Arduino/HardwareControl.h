#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include <Centipede.h>

#include "hardware/interface/IHardwareInterface.h"
#include "hardware/interface/IWater.h"

#include "includes/Vector.h"

#define INPUT_WATER_2        (16)
#define INPUT_WATER_1        (17)
#define INPUT_TEMPERATURE_2  (18)
#define INPUT_TEMPERATURE_1  (19)

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
