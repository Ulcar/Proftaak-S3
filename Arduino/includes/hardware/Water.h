#ifndef WATER_H
#define WATER_H

#include "interface/IWater.h"

#define INPUT_PRESSURE (23)
#define INPUT_WATER_1  (17)
#define INPUT_WATER_2  (16)

#define OUTPUT_SINK    (13)
#define OUTPUT_DRAIN   (14)

class Water : public IWater
{
public:
    void Initialize(ICentipedeShield* centipede);

    WaterLevel GetLevel();
    bool HasPressure();

    void SetSink(HardwareState state);
    void SetDrain(HardwareState state);
};

#endif
