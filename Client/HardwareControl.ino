#include "includes/hardware/HardwareControl.h"

HardwareControl::HardwareControl(
    ICentipedeShield* centipede,
    IStatusIndicator* statusIndicator,
    IControls* controls,
    IHeater* heater,
    IMotor* motor,
    IWater* water
)
    : _centipede(centipede)
    , _statusIndicator(statusIndicator)
    , _controls(controls)
    , _heater(heater)
    , _motor(motor)
    , _water(water)
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

    _statusIndicator->Initialize();
    _controls->Initialize(_centipede);
    _heater->Initialize(_centipede);
    _motor->Initialize(_centipede);
    _water->Initialize(_centipede);

    _statusIndicator->SetStatus(S_DECOUPLED);
}

HardwareControl::~HardwareControl()
{
    delete _statusIndicator;

    delete _controls;
    delete _heater;
    delete _motor;
    delete _water;

    delete _centipede;
}

IStatusIndicator* HardwareControl::GetStatusIndicator()
{
    return _statusIndicator;
}

IControls* HardwareControl::GetControls()
{
    return _controls;
}

IHeater* HardwareControl::GetHeater()
{
    return _heater;
}

IMotor* HardwareControl::GetMotor()
{
    return _motor;
}

IWater* HardwareControl::GetWater()
{
    return _water;
}
