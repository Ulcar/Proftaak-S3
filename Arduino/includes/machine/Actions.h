#ifndef ACTIONS_H
#define ACTIONS_H

#include "../hardware/HardwareControl.h"

class IAction
{
public:
    virtual void Handle(HardwareControl& control) = 0;
};

class HeatAction : public IAction
{
public:
    HeatAction(int level);

    void Handle(HardwareControl& control);

private:
    int _level;
};

class FillWaterAction : public IAction
{
public:
    FillWaterAction(int level);

    void Handle(HardwareControl& control);

private:
    int _level;
};

class MotorRotate : public IAction
{
public:
    MotorRotate(MotorDirection direction, MotorSpeed speed);

    void Handle();
    bool IsDone();
private:
    HardwareControl& _control;
    MotorDirection direction;
    MotorSpeed speed;
};

#endif
