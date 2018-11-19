#include "Machine.h"

HeatAction::HeatAction(int level)
    : _level(level)
{}

void HeatAction::Handle(HardwareControl& control)
{
    Serial.print("Heating: ");
    Serial.println(_level);
}

FillWaterAction::FillWaterAction(int level)
    : _level(level)
{}

void FillWaterAction::Handle(HardwareControl& control)
{
    /*
    Water* water = dynamic_cast<Water*>(control.GetInterface("water"));

    water->OpenValve();

    while (water->GetLevel() < _level);

    water->CloseValve();
    */

    Serial.print("Fill Water: ");
    Serial.println(_level);
}

Program::Program(int number)
    : _number(number)
{}

int Program::GetNumber()
{
    return _number;
}

void Program::AddAction(Action* action)
{
    _actions.push_back(action);
}

void Program::Start(HardwareControl& control)
{
    for (int i = 0; i < _actions.size(); ++i)
    {
        _actions[i]->Handle(control);
    }
}

void Machine::StartProgram(int number)
{
    for (int i = 0; i < _programs.size(); ++i)
    {
        if (_programs[i]->GetNumber() == number)
        {
            _programs[i]->Start(_control);
            return;
        }
    }

    _serial->SendMessage("Couldn't find program.\n");
}

void Machine::NewProgram(int number, Vector<Action*>& actions)
{
    Program* program = new Program(number);

    for (int i = 0; i < actions.size(); ++i)
    {
        program->AddAction(actions[i]);
    }

    _programs.push_back(program);
}

Machine::Machine(HardwareControl& control, INetworkClient* serial)
    : _control(control)
    , _serial(serial)
{}
