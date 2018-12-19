#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoSTL.h>

#include "Actions.h"

class Program
{
public:
    Program(int number);

    void Update();

    void GoToNextAction();

    int GetNumber();
    void AddAction(IAction* action);

    void Start(HardwareControl& control);

private:
    int _number;

    std::vector<IAction*> _actions;
    IAction* _currentAction;
    int _currentActionIndex;
};

#endif
