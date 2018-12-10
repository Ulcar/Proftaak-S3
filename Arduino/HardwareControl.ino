#include "includes/hardware/HardwareControl.h"

HardwareControl::HardwareControl(ICentipedeShield* centipede, IControls* controls, IHeater* heater, IMotor* motor, IWater* water)
    : _centipede(centipede)
    , _controls(controls)
    , _heater(heater)
    , _motor(motor)
    , _water(water)
{
    // ...
}

HardwareControl::~HardwareControl()
{
    delete _centipede;
    delete _controls;
    delete _heater;
    delete _motor;
    delete _water;
}

void HardwareControl::Initialize()
{
    _centipede->Initialize();

    for (int i = 0; i < 16; ++i)
    {
        _centipede->PinMode(i, OUTPUT);
    }

    _centipede->DigitalWrite(OUTPUT_KEYSELECT, HIGH);
    _centipede->DigitalWrite(OUTPUT_GROUP_2, LOW);
    _centipede->DigitalWrite(OUTPUT_GROUP_1, LOW);
    _centipede->DigitalWrite(OUTPUT_STROBE, LOW);
    _centipede->DigitalWrite(OUTPUT_DATA_C, LOW);
    _centipede->DigitalWrite(OUTPUT_DATA_B, LOW);
    _centipede->DigitalWrite(OUTPUT_DATA_A, LOW);

    _controls->Initialize(_centipede);
    _heater->Initialize(_centipede);
    _motor->Initialize(_centipede);
    _water->Initialize(_centipede);
}
