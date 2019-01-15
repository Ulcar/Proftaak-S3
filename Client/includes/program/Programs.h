#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <ArduinoSTL.h>
#include <SD.h>

#include "../client/MainClient.h"
#include "Actions.h"
#include "Program.h"

typedef void (*OnProgramDoneCallback)();

class Programs
{
public:
    Programs(HardwareControl* control, MainClient* client, OnProgramDoneCallback callback);
    ~Programs();

    void Reset();
    void Update();

    void Add(int number, std::vector<IAction*> actions);
    void Load(File dir);
    bool Start(int number);

    void AllowTakeWater();
    void AllowHeatUp();

private:
    std::vector<Program*> _programs;

    OnProgramDoneCallback _onProgramDone;
    HardwareControl* _control;
    Program* _currentProgram;
    MainClient* _client;

    bool Add(Stream& json);

    Programs(const Programs& other);
    Programs& operator=(const Programs& other);
};

#endif
