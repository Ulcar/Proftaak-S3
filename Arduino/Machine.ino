#include "includes/machine/Machine.h"

Machine::Machine(HardwareControl& control, IClient* client)
    : _control(control)
    , _client(client)
{
    // ...
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

    //_client->SendMessage("Couldn't find program.\n");
}

void Machine::NewProgram(int number, Vector<IAction*>& actions)
{
    Program* program = new Program(number);

    for (int i = 0; i < actions.size(); ++i)
    {
        program->AddAction(actions[i]);
    }

    _programs.push_back(program);
}
