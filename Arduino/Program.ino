#include "includes/machine/Program.h"

Program::Program(int number)
    : _number(number)
{
    // ...
}

int Program::GetNumber()
{
    return _number;
}

void Program::AddAction(IAction* action)
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
