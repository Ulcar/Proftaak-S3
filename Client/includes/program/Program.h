#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoJson.h>
#include <ArduinoSTL.h>

#include "../client/MainClient.h"

#include "Actions.h"

class Program
{
public:
    Program(HardwareControl* control, MainClient* client);

    bool Load(String json);
    void Start();
    bool Update();
    void AddAction(IAction* action);

    void AllowTakeWater();
    void AllowHeatUp();

    int Program::GetNumber();

private:
    std::vector<IAction*> _actions;

    HardwareControl* _control;
    IAction* _currentAction;
    MainClient* _client;

    bool _started;
    int _number;
    int _nextActionIndex;

    IAction* CreateAction(int nr, JsonObject& args);
    bool SetNextAction();
};

#endif
