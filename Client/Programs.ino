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
        bool result = _currentProgram->Update();

        // If the result is 'false' we know that the program is done.
        if (!result && _onProgramDone != NULL)
        {
            _currentProgram = NULL;

            _onProgramDone();
        }
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
            _currentProgram->Start();

            return true;
        }
    }

    return false;
}
