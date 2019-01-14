#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <ArduinoSTL.h>

#include "../client/MainClient.h"
#include "Actions.h"
#include "Program.h"

typedef void (*OnProgramDoneCallback)();

class Programs
{
public:
    Programs(HardwareControl* control, MainClient* client, OnProgramDoneCallback callback);
    ~Programs();

    void Update();

    bool Add(String json);
    bool Start(int number);

    void AllowTakeWater();
    void AllowHeatUp();

private:
    std::vector<Program*> _programs;

    OnProgramDoneCallback _onProgramDone;
    HardwareControl* _control;
    Program* _currentProgram;
    MainClient* _client;

    Programs(const Programs& other);
    Programs& operator=(const Programs& other);
};

#endif
