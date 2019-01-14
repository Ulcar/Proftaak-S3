#ifndef ACTIONS_H
#define ACTIONS_H

#include "../hardware/HardwareControl.h"
#include "../hardware/StatusIndicator.h"
#include "../hardware/Controls.h"
#include "../hardware/Heater.h"
#include "../hardware/Motor.h"
#include "../hardware/Water.h"

#include "../client/MainClient.h"

#define DELAY_TIME_POWER (2000)
#define DELAY_TIME_WATER (2000)

class IAction
{
public:
    virtual ~IAction() { };

    virtual void Handle() = 0;
    virtual bool IsDone() = 0;

    void AllowTakeWater()
    {
        _mayTakeWater = true;
    }

    void AllowHeatUp()
    {
        _mayHeatUp = true;
    }

    void SetHardwareControl(HardwareControl* control)
    {
        _control = control;
    }

    void SetClient(MainClient* client)
    {
        _client = client;
    }

protected:
    HardwareControl* _control;
    MainClient* _client;

    bool _mayTakeWater;
    bool _mayHeatUp;
};

class SoapAction : public IAction
{
public:
    SoapAction(HardwareState state, int dispenser);

    void Handle();
    bool IsDone();

private:
    HardwareState _state;
    int _dispenser;
};

class BuzzerAction : public IAction
{
public:
    BuzzerAction(HardwareState state);

    void Handle();
    bool IsDone();

private:
    HardwareState _state;
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

class RequestPowerAction : public IAction
{
public:
    RequestPowerAction(int watt);

    void Handle();
    bool IsDone();

private:
    unsigned long _startMs;
    int _watt;
};

class RequestWaterAction : public IAction
{
public:
    RequestWaterAction(int liters);

    void Handle();
    bool IsDone();

private:
    unsigned long _startMs;
    int _liters;
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
