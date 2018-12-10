#ifndef MACHINE_H
#define MACHINE_H

#include "../hardware/HardwareControl.h"
#include "../client/IClient.h"
#include "Program.h"
#include "Actions.h"

class Machine
{
public:
    Machine(HardwareControl& control, IClient* client);

    void StartProgram(int number);
    void NewProgram(int number, Vector<IAction*>& actions);

private:
    HardwareControl& _control;
    IClient* _client;

    Vector<Program*> _programs;
};

#endif
