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


MotorRotateLeft::MotorRotateLeft()
{
    //TODO
    
}

void MotorRotateLeft::Handle(HardwareControl& control)
{
    IMotor* motor = control.GetMotor();
    motor->SetDirection(MotorDirection::MD_LEFT);

    Serial.println("Start rotating left!");
}


MotorRotateRight::MotorRotateRight()
{
    //TODO
    
}

void MotorRotateRight::Handle(HardwareControl& control)
{
    IMotor* motor = control.GetMotor();
    motor->SetDirection(MotorDirection::MD_RIGHT);

    Serial.println("Start rotating right!");
}