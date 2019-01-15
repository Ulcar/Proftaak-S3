#include "includes/program/Programs.h"

Programs::Programs(HardwareControl* control, MainClient* client, OnProgramDoneCallback callback)
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

void Programs::Load(File dir)
{
    while (1)
    {
        File entry = dir.openNextFile();

        if (!entry)
        {
            break;
        }

        if (entry.isDirectory())
        {
            continue;
        }

        String filename(entry.name());

        if (filename.startsWith("PROG"))
        {
            Serial.println("Reading " + filename);

            Add(entry);
        }

        entry.close();
    }

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

bool Programs::Add(Stream& file)
{
    Program* program = new Program(_control, _client);

    program->Load(file);

    _programs.push_back(program);
}
