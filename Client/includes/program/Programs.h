#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <ArduinoSTL.h>

#include "Actions.h"
#include "Program.h"

typedef void (*OnProgramDoneCallback)();

class Programs
{
public:
    Programs(HardwareControl* control, IClient* client);

    void Update();

    bool Add(String json);
    bool Start(int number);

    void SetOnProgramDone(OnProgramDoneCallback callback)
    {
        _onProgramDone = callback;
    }

private:
    std::vector<Program*> _programs;

    OnProgramDoneCallback _onProgramDone;
    HardwareControl* _control;
    Program* _currentProgram;
    IClient* _client;
};

#endif
