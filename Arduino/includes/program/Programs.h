#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <ArduinoSTL.h>

#include "Actions.h"
#include "Program.h"

class Programs
{
public:
    Programs(HardwareControl* control, IClient* client);

    void Update();

    void Add(int number, std::vector<IAction*> actions);
    bool Start(int number);

private:
    HardwareControl* _control;
    IClient* _client;

    std::vector<Program*> _programs;
    Program* _currentProgram;
};

#endif
