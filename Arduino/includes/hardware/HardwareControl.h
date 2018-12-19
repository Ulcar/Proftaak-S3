#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include "interface/ICentipedeShield.h"
#include "interface/IControls.h"
#include "interface/IHeater.h"
#include "interface/IMotor.h"
#include "interface/IWater.h"

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
    HardwareControl(ICentipedeShield* centipede, IControls* controls, IHeater* heater, IMotor* motor, IWater* water);
    ~HardwareControl();

    IControls* GetControls() { return _controls; }
    IHeater* GetHeater() { return _heater; }
    IMotor* GetMotor() { return _motor; }
    IWater* GetWater() { return _water; }

private:
    ICentipedeShield* _centipede;

    IControls* _controls;
    IHeater* _heater;
    IMotor* _motor;
    IWater* _water;
};

#endif
