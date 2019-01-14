#include "includes/program/Actions.h"

//
// AddSoapAction
//=============

SoapAction::SoapAction(HardwareState state, int dispenser)
    : _state(state)
    , _dispenser(dispenser)
{
    _control = NULL;
    _client = NULL;
}

void SoapAction::Handle()
{
    Controls* controls = (Controls *) _control->GetControls();

    controls->SetSoap(_state, _dispenser);
}

bool SoapAction::IsDone()
{
    return true;
}

//
// BuzzerAction
//=============

BuzzerAction::BuzzerAction(HardwareState state)
    : _state(state)
{
    _control = NULL;
    _client = NULL;
}

void BuzzerAction::Handle()
{
    Controls* controls = (Controls *) _control->GetControls();

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
    _control = NULL;
    _client = NULL;
}

void DrainWaterAction::Handle()
{
    Water* water = (Water *) _control->GetWater();

    if (water->GetSinkState() != STATE_ON)
    {
        water->SetSink(STATE_ON);
    }
}

bool DrainWaterAction::IsDone()
{
    Water* water = (Water *) _control->GetWater();

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
    _control = NULL;
    _client = NULL;
}

void HeatAction::Handle()
{
    Heater* heater = (Heater *) _control->GetHeater();

    if (heater->GetState() != STATE_ON)
    {
        heater->Set(heater->GetTemperature() < _temp ? STATE_ON : STATE_OFF);
    }
}

bool HeatAction::IsDone()
{
    Heater* heater = (Heater *) _control->GetHeater();

    if (heater->GetTemperature() == _temp)
    {
        heater->Set(STATE_OFF);

        _client->SendMessage(M_STOP_HEAT_UP, { "0" });

        return true;
    }

    return false;
}

//
// FillWaterAction
//==================

FillWaterAction::FillWaterAction(WaterLevel level)
    : _level(level)
{
    _control = NULL;
    _client = NULL;
}

void FillWaterAction::Handle()
{
    Water* water = (Water *) _control->GetWater();

    if (water->GetDrainState() != STATE_ON)
    {
        water->SetDrain(STATE_ON);
    }
}

bool FillWaterAction::IsDone()
{
    Water* water = (Water *) _control->GetWater();

    if (water->GetLevel() == _level)
    {
        _client->SendMessage(M_STOP_TAKE_WATER, { "0" });

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
{
    _mayHeatUp = false;
    _control = NULL;
    _client = NULL;
}

void RequestPowerAction::Handle()
{
    StatusIndicator* statusIndicator = (StatusIndicator *) _control->GetStatusIndicator();
    statusIndicator->SetStatus(S_NO_POWER);

    unsigned long currentMs = millis();

    if (_startMs == 0 || currentMs - _startMs > DELAY_TIME_POWER)
    {
        _startMs = currentMs;

        _client->SendMessage(M_MAY_HEAT_UP, { String(_watt) });
    }
}

bool RequestPowerAction::IsDone()
{
    bool result = _mayHeatUp;

    if (result)
    {
        StatusIndicator* statusIndicator = (StatusIndicator *) _control->GetStatusIndicator();
        statusIndicator->SetStatus(S_BUSY);

        _mayHeatUp = false;
        _startMs = 0;
    }

    return result;
}

//
// RequestWaterAction
//==================

RequestWaterAction::RequestWaterAction(int liters)
    : _startMs(0)
    , _liters(liters)
{
    _mayTakeWater = false;
    _control = NULL;
    _client = NULL;
}

void RequestWaterAction::Handle()
{
    StatusIndicator* statusIndicator = (StatusIndicator *) _control->GetStatusIndicator();
    statusIndicator->SetStatus(S_NO_WATER);

    unsigned long currentMs = millis();

    if (_startMs == 0 || currentMs - _startMs > DELAY_TIME_WATER)
    {
        _startMs = currentMs;

        _client->SendMessage(M_MAY_TAKE_WATER, { String(_liters) });
    }
}

bool RequestWaterAction::IsDone()
{
    bool result = _mayTakeWater;

    if (result)
    {
        StatusIndicator* statusIndicator = (StatusIndicator *) _control->GetStatusIndicator();
        statusIndicator->SetStatus(S_BUSY);

        _mayTakeWater = false;
        _startMs = 0;
    }

    return result;
}

//
// MotorRotateAction
//==================

MotorRotateAction::MotorRotateAction(MotorDirection direction, MotorSpeed speed)
    : _direction(direction)
    , _speed(speed)
{
    _control = NULL;
    _client = NULL;
}

void MotorRotateAction::Handle()
{
    Motor* motor = (Motor *) _control->GetMotor();

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
    _control = NULL;
    _client = NULL;
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
