#ifndef MACHINE_H
#define MACHINE_H

#include "includes/Vector.h"

#include "HardwareControl.h"
#include "INetworkClient.h"

class IAction
{
public:
    virtual void Handle(HardwareControl& control) = 0;
};

class HeatAction : public IAction
{
public:
    HeatAction(int level);

    void Handle(HardwareControl& control);

private:
    int _level;
};

class FillWaterAction : public IAction
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
    void AddAction(IAction* action);
    void Start(HardwareControl& control);

private:
    int _number;
    Vector<IAction*> _actions;
};

class Machine
{
public:
    Machine(HardwareControl& control, INetworkClient* client);

    void StartProgram(int number);
    void NewProgram(int number, Vector<IAction*>& actions);

private:
    HardwareControl& _control;
    INetworkClient* _client;

    Vector<Program*> _programs;
};

#endif
