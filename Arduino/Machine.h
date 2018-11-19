#ifndef MACHINE_H
#define MACHINE_H

#include "includes/Vector.h"

#include "HardwareControl.h"
#include "INetworkClient.h"

class Action
{
public:
    virtual void Handle(HardwareControl& control) = 0;
};

class HeatAction : public Action
{
public:
    HeatAction(int level);

    void Handle(HardwareControl& control);

private:
    int _level;
};

class FillWaterAction : public Action
{
public:
    FillWaterAction(int level);

    void Handle(HardwareControl& control);

private:
    int _level;
};

class Program
{
public:
    Program(int number);

    int GetNumber();
    void AddAction(Action* action);
    void Start(HardwareControl& control);

private:
    int _number;
    Vector<Action*> _actions;
};

class Machine
{
public:
    Machine(HardwareControl& control, INetworkClient* serial);

    void StartProgram(int number);
    void NewProgram(int number, Vector<Action*>& actions);

private:
    HardwareControl& _control;
    INetworkClient* _serial;
    Vector<Program*> _programs;
};

#endif
