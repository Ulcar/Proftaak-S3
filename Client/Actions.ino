#include "includes/program/Actions.h"

//
// IAction
//=============

void IAction::SetHardwareControl(HardwareControl* control)
{
    _control = control;
}

void IAction::SetClient(IClient* client)
{
    _client = client;
}

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
    controls->SetSoap(STATE_OFF, _dispenser);
}

bool AddSoapAction::IsDone()
{
    return true;
}

//
// BuzzerAction
//=============

BuzzerAction::BuzzerAction(int ms)
    : _ms(ms)
{
    // ...
}

void BuzzerAction::Handle()
{
    Controls* controls = _control->GetControls();

    controls->EnableBuzzer(_ms);
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
    Serial.println("DrainWaterAction::Handle()");

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
    Serial.println("HeatAction::Handle()");

    Heater* heater = _control->GetHeater();

    if (heater->GetState() != STATE_ON)
    {
        HardwareState state = heater->GetTemperature() < _temp
            ? STATE_ON
            : STATE_OFF;

        heater->Set(state);
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
    Serial.println("FillWaterAction::Handle()");

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
        Serial.println("Asking for power...");

        String parameters[] = { String(_watt) };
        _client->SendMessage(M_MAY_HEAT_UP, parameters, 1);

        std::vector<String> response = _client->ReadMessage(true);

        if (response[0] == String(M_MAY_HEAT_UP) && response[1] == "0")
        {
            _mayUsePower = true;
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
        Serial.println("Asking for water...");

        String parameters[] = { String(_liters) };
        _client->SendMessage(M_MAY_TAKE_WATER, parameters, 1);

        std::vector<String> response = _client->ReadMessage(true);

        if (response[0] == String(M_MAY_TAKE_WATER) && response[1] == "0")
        {
            _mayTakeWater = true;
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
    // Nothing to do...
}

void MotorRotateAction::Handle()
{
    Serial.println("MotorRotateAction::Handle()");

    Motor* motor = _control->GetMotor();

    motor->SetDirection(_direction);
    motor->SetSpeed(_speed);

    Serial.println("Rotating: " + String(_direction) + " with speed: " + String(_speed));
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
    // Nothing to do...
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
    return millis() - _startMs > _ms;
}
