#include "HardwareControl.h"

HardwareControl::HardwareControl()
    : _centipede(Centipede())
{
    // ...
}

HardwareControl::~HardwareControl()
{
    delete _controls;
    delete _heater;
    delete _motor;
    delete _water;
}

void HardwareControl::Initialize()
{
    Wire.begin(9600);

    _centipede.initialize();

    for (int i = 0; i < 16; ++i)
    {
        _centipede.pinMode(i, OUTPUT);
    }

    _centipede.digitalWrite(OUTPUT_KEYSELECT, HIGH);
    _centipede.digitalWrite(OUTPUT_GROUP_2,   LOW);
    _centipede.digitalWrite(OUTPUT_GROUP_1,   LOW);
    _centipede.digitalWrite(OUTPUT_STROBE,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_C,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_B,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_A,    LOW);

    _controls->Initialize(_centipede);
    _heater->Initialize(_centipede);
    _motor->Initialize(_centipede);
    _water->Initialize(_centipede);
}
