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

class HeatAction : public IAction
{
public:
    HeatAction(Temperature temp);

    void Handle();
    bool IsDone();

    /*
    void SetHardwareControl(HardwareControl* control);
    void SetClient(IClient* client);
    */

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

#endif
