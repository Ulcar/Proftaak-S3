#ifndef HEATER_H
#define HEATER_H

#include "interface/IHeater.h"

#define INPUT_TEMPERATURE_1 (19)
#define INPUT_TEMPERATURE_2 (18)

#define OUTPUT_HEATER       ( 5)

class Heater : public IHeater
{
public:
    Heater();
    ~Heater();

    void Initialize(ICentipedeShield* centipede);
    void Set(HardwareState state);

    HardwareState GetState();
    Temperature GetTemperature();

private:
    HardwareState _state;

    Heater(const Heater& other);
    Heater& operator=(const Heater& other);
};

#endif
