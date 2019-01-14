#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoSTL.h>

#include "Actions.h"

class Program
{
public:
    Program(int number, HardwareControl* control, IClient* client);

    void Start();
    bool Update();
    bool SetNextAction();
    void AddAction(IAction* action);

    void AllowTakeWater();
    void AllowHeatUp();

    int Program::GetNumber();

private:
    std::vector<IAction*> _actions;

    HardwareControl* _control;
    IAction* _currentAction;
    IClient* _client;

    bool _started;
    int _number;
    int _nextActionIndex;
};

#endif
