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


void MotorRotate::Handle()
{
    IMotor* motor = _control.GetMotor();

    motor->SetDirection(direction);
    motor->SetSpeed(speed);

    Serial.println("Rotating: " + String(direction) + " with speed: " + String(speed));
}

bool MotorRotate::IsDone()
{
    return true;
}

MotorRotate::MotorRotate(MotorDirection direction, MotorSpeed speed)
{
    this->direction = direction;
    this->speed = speed;
}