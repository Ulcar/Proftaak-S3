#ifndef PROGRAM_H
#define PROGRAM_H

#include "../library/Vector.h"
#include "Actions.h"

class Program
{
public:
    Program(int number);

    int GetNumber();
    void AddAction(IAction* action);
    void Start(HardwareControl& control);

private:
    int _number;
    Vector<IAction*> _actions;
};

#endif
