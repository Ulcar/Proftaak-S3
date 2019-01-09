#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoSTL.h>

#include "Actions.h"

class Program
{
public:
    Program(HardwareControl* control, IClient* client);

    void Start();
    bool Update();
    bool SetNextAction();
    void AddAction(IAction* action);

    void AllowTakeWater();
    void AllowHeatUp();

    void SetNumber(int number)
    {
        _number = number;
    }

    int Program::GetNumber()
    {
        return _number;
    }

private:
    std::vector<IAction*> _actions;

    HardwareControl* _control;
    IAction* _currentAction;
    IClient* _client;

    bool _started;
    int _number;
    int _currentActionIndex;
};

#endif
