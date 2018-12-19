#ifndef MACHINE_H
#define MACHINE_H

#include <ArduinoSTL.h>

#include "../hardware/HardwareControl.h"
#include "../client/IClient.h"
#include "Program.h"
#include "Actions.h"

class Machine
{
public:
    Machine(HardwareControl& control, IClient* client);

    void Update();

    void NewProgram(int number, std::vector<IAction*>& actions);
    bool SetProgram(int number);

private:
    HardwareControl& _control;
    IClient* _client;

    std::vector<Program*> _programs;
    Program* _currentProgram;
};

#endif
