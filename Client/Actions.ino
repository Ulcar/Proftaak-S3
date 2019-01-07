#include "includes/program/Actions.h"

//
// AddSoapAction
//=============

AddSoapAction::AddSoapAction(int dispenser)
    : _dispenser(dispenser)
{
    // ...
}

void AddSoapAction::Handle()
{
    Controls* controls = _control->GetControls();

    controls->SetSoap(STATE_ON, _dispenser);
}

bool AddSoapAction::IsDone()
{
    return true;
}

//
// BuzzerAction
//=============

BuzzerAction::BuzzerAction(HardwareState state)
    : _state(state)
{
    // ...
}

void BuzzerAction::Handle()
{
    Controls* controls = _control->GetControls();

    controls->SetBuzzer(_state);
}

bool BuzzerAction::IsDone()
{
    return true;
}

//
// DrainWaterAction
//=============

DrainWaterAction::DrainWaterAction()
{
    // ...
}

void DrainWaterAction::Handle()
{
    Water* water = _control->GetWater();

    if (water->GetSinkState() != STATE_ON)
    {
        water->SetSink(STATE_ON);
    }
}

bool DrainWaterAction::IsDone()
{
    Water* water = _control->GetWater();

    if (water->GetLevel() == WL_EMPTY)
    {
        water->SetSink(STATE_OFF);

        return true;
    }

    return false;
}

//
// HeatAction
//=============

HeatAction::HeatAction(Temperature temp)
    : _temp(temp)
{
    // ...
}

void HeatAction::Handle()
{
    Heater* heater = _control->GetHeater();

    if (heater->GetState() != STATE_ON)
    {
        heater->Set(heater->GetTemperature() < _temp ? STATE_ON : STATE_OFF);
    }
}

bool HeatAction::IsDone()
{
    Heater* heater = _control->GetHeater();

    return heater->GetTemperature() == _temp;
}

//
// FillWaterAction
//==================

FillWaterAction::FillWaterAction(WaterLevel level)
    : _level(level)
{
    // ...
}

void FillWaterAction::Handle()
{
    Water* water = _control->GetWater();

    if (water->GetDrainState() != STATE_ON)
    {
        water->SetDrain(STATE_ON);
    }
}

bool FillWaterAction::IsDone()
{
    Water* water = _control->GetWater();

    if (water->GetLevel() == _level)
    {
        water->SetDrain(STATE_OFF);

        return true;
    }

    return false;
}

//
// RequestPowerAction
//==================

RequestPowerAction::RequestPowerAction(int watt)
    : _watt(watt)
    , _mayUsePower(false)
{
    // ...
}

void RequestPowerAction::Handle()
{
    while (!_mayUsePower)
    {
        _client->SendMessage(M_MAY_HEAT_UP, { String(_watt) });

        std::vector<String> response = _client->ReadMessage(true);

        if (response[0] == String(M_MAY_HEAT_UP) && response[1] == "0")
        {
            _mayUsePower = true;
        }
        else
        {
            delay(500);
        }
    }
}

bool RequestPowerAction::IsDone()
{
    return _mayUsePower;
}

//
// RequestWaterAction
//==================

RequestWaterAction::RequestWaterAction(int liters)
    : _liters(liters)
    , _mayTakeWater(false)
{
    // ...
}

void RequestWaterAction::Handle()
{
    while (!_mayTakeWater)
    {
        _client->SendMessage(M_MAY_TAKE_WATER, { String(_liters) });

        std::vector<String> response = _client->ReadMessage(true);

        if (response[0] == String(M_MAY_TAKE_WATER) && response[1] == "0")
        {
            _mayTakeWater = true;
        }
        else
        {
            delay(500);
        }
    }
}

bool RequestWaterAction::IsDone()
{
    return _mayTakeWater;
}

//
// MotorRotateAction
//==================

MotorRotateAction::MotorRotateAction(MotorDirection direction, MotorSpeed speed)
    : _direction(direction)
    , _speed(speed)
{
    // ...
}

void MotorRotateAction::Handle()
{
    Motor* motor = _control->GetMotor();

    motor->SetDirection(_direction);
    motor->SetSpeed(_speed);
}

bool MotorRotateAction::IsDone()
{
    return true;
}

//
// DelayAction
//==================

DelayAction::DelayAction(unsigned long ms)
    : _ms(ms)
    , _startMs(0)
{
    // ...
}

void DelayAction::Handle()
{
    if (_startMs == 0)
    {
        _startMs = millis();
    }
}

bool DelayAction::IsDone()
{
    bool result = millis() - _startMs > _ms;

    if (result)
    {
        _startMs = 0;
    }

    return result;
}
