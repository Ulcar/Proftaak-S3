#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include <Centipede.h>
#include <Wire.h>

#include "hardware/interface/IControls.h"
#include "hardware/interface/IHeater.h"
#include "hardware/interface/IMotor.h"
#include "hardware/interface/IWater.h"

#define OUTPUT_GROUP_2   ( 0)
#define OUTPUT_GROUP_1   ( 1)
#define OUTPUT_STROBE    ( 2)
#define OUTPUT_KEYSELECT ( 3)
#define OUTPUT_DATA_C    ( 8)
#define OUTPUT_DATA_B    ( 9)
#define OUTPUT_DATA_A    (10)

#define INPUT_IN_1       (22)
#define INPUT_IN_2       (21)
#define INPUT_IN_3       (20)

class HardwareControl
{
public:
    HardwareControl();
    ~HardwareControl();

    void Initialize();

    void SetControls(IControls* controls) { _controls = controls; }
    IControls* GetControls() { return _controls; }

    void SetHeater(IHeater* heater) { _heater = heater; }
    IHeater* GetHeater() { return _heater; }

    void SetMotor(IMotor* motor) { _motor = motor; }
    IMotor* GetMotor() { return _motor; }

    void SetWater(IWater* water) { _water = water; }
    IWater* GetWater() { return _water; }

private:
    Centipede _centipede;

    IControls* _controls;
    IHeater* _heater;
    IMotor* _motor;
    IWater* _water;
};

#endif
