#include "includes/machine/Machine.h"

Machine::Machine(HardwareControl& control, IClient* client)
    : _control(control)
    , _client(client)
{
    // ...
}

void Machine::Update()
{
    _currentProgram->Update();
}

void Machine::NewProgram(int number, std::vector<IAction*>& actions)
{
    Program* program = new Program(number);

    for (int i = 0; i < actions.size(); ++i)
    {
        IAction* action = actions[i];

        action->SetHardwareControl(&_control);
        action->SetClient(_client);

        program->AddAction(action);
    }

    _programs.push_back(program);
}

bool Machine::SetProgram(int number)
{
    for (int i = 0; i < _programs.size(); ++i)
    {
        if (_programs[i]->GetNumber() == number)
        {
            _currentProgram = _programs[i];
            return true;
        }
    }

    return false;
}
