#include "includes/program/Programs.h"

Programs::Programs(HardwareControl* control, IClient* client, OnProgramDoneCallback callback)
    : _onProgramDone(callback)
    , _currentProgram(NULL)
    , _control(control)
    , _client(client)
{
    // ...
}

Programs::~Programs()
{
    for (int i = 0; i < _programs.size(); ++i)
    {
        delete _programs[i];
    }
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

bool Programs::Add(String json)
{
    Program* program = new Program(_control, _client);

    program->Load(json);

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

void Programs::AllowTakeWater()
{
    if (_currentProgram != NULL)
    {
        _currentProgram->AllowTakeWater();
    }
}

void Programs::AllowHeatUp()
{
    if (_currentProgram != NULL)
    {
        _currentProgram->AllowHeatUp();
    }
}
