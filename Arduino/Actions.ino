#include "includes/machine/Actions.h"

//
// HeatAction
//=============

HeatAction::HeatAction(int level)
    : _level(level)
{
    // ...
}

void HeatAction::Handle(HardwareControl& control)
{
    Serial.println("Heating: " + String(_level));
}

//
// FillWaterAction
//==================

FillWaterAction::FillWaterAction(int level)
    : _level(level)
{
    // ...
}

void FillWaterAction::Handle(HardwareControl& control)
{
    Serial.println("Fill Water: " + String(_level));
}
