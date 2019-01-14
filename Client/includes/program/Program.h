#ifndef PROGRAM_H
#define PROGRAM_H

#include <ArduinoJson.h>
#include <ArduinoSTL.h>

#include "Actions.h"

class Program
{
public:
    Program(HardwareControl* control, IClient* client);

    bool Load(String json);
    void Start();
    bool Update();
    void AddAction(IAction* action);

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

    IAction* CreateAction(int nr, JsonObject& args);
    bool SetNextAction();
};

#endif
