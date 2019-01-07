#include "includes/program/Programs.h"

Programs::Programs(HardwareControl* control, IClient* client)
    : _currentProgram(NULL)
    , _control(control)
    , _client(client)
{
    // ...
}

void Programs::Update()
{
    if (_currentProgram != NULL)
    {
        _currentProgram->Update();
    }
}

void Programs::Add(int number, std::vector<IAction*> actions)
{
    Program* program = new Program(_control, _client);
    program->SetNumber(number);

    for (int i = 0; i < actions.size(); ++i)
    {
        program->AddAction(actions[i]);
    }

    _programs.push_back(program);
}

bool Programs::Start(int number)
{
    for (int i = 0; i < _programs.size(); ++i)
    {
        if (_programs[i]->GetNumber() == number)
        {
            _currentProgram = _programs[i];
            _currentProgram->SetNextAction();

            return true;
        }
    }

    return false;
}
