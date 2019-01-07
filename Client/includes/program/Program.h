#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoSTL.h>

#include "Actions.h"

class Program
{
public:
    Program(HardwareControl* control, IClient* client);

    void SetNumber(int number);
    int GetNumber();

    void Update();
    void Reset();
    void SetNextAction();
    void AddAction(IAction* action);

private:
    HardwareControl* _control;
    IClient* _client;

    int _number;

    std::vector<IAction*> _actions;
    IAction* _currentAction;
    int _currentActionIndex;
};

#endif
