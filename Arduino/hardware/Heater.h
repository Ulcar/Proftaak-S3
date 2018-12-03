#ifndef HEATER_H
#define HEATER_H

#include "interface/IHardwareInterface.h"
#include "interface/IHeater.h"

#define INPUT_TEMPERATURE_1 (39)
#define INPUT_TEMPERATURE_2 (37)

#define OUTPUT_HEATER       ( 5)

class Heater : public IHeater, public IHardwareInterface
{
public:
    Heater();
    ~Heater();

    void Initialize();

    void Set(HardwareState state);
    Temperature GetTemperature();
};

#endif
