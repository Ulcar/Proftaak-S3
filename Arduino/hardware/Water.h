#ifndef WATER_H
#define WATER_H

#include "interface/IHardwareInterface.h"
#include "interface/IWater.h"

class Water : public IWater, public IHardwareInterface
{
public:
    Water();
    ~Water();

    int GetLevel();
    bool GetPressure();
};

#endif
