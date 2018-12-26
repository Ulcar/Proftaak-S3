#ifndef ACTIONS_H
#define ACTIONS_H

#include "../hardware/HardwareControl.h"

class IAction
{
public:
    virtual ~IAction() { };

    virtual void Handle() = 0;
    virtual bool IsDone() = 0;

    void SetHardwareControl(HardwareControl* control);
    void SetClient(IClient* client);

protected:
    HardwareControl* _control;
    IClient* _client;
};

class BuzzerAction : public IAction
{
public:
    BuzzerAction(int ms);

    void Handle();
    bool IsDone();

private:
    int _ms;
};

class DrainWaterAction : public IAction
{
public:
    DrainWaterAction();

    void Handle();
    bool IsDone();
};

class HeatAction : public IAction
{
public:
    HeatAction(Temperature temp);

    void Handle();
    bool IsDone();

private:
    Temperature _temp;
};

class FillWaterAction : public IAction
{
public:
    FillWaterAction(WaterLevel level);

    void Handle();
    bool IsDone();

private:
    WaterLevel _level;
};

class RequestWaterAction : public IAction
{
public:
    RequestWaterAction();

    void Handle();
    bool IsDone();

private:
    bool _mayTakeWater;
};

class MotorRotateAction : public IAction
{
public:
    MotorRotateAction(MotorDirection direction, MotorSpeed speed);

    void Handle();
    bool IsDone();

private:
    MotorDirection _direction;
    MotorSpeed _speed;
};

class DelayAction : public IAction
{
public:
    DelayAction(unsigned long ms);

    void Handle();
    bool IsDone();

private:
    unsigned long _ms;
    unsigned long _startMs;
};

#endif
