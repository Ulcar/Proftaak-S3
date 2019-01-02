#include "includes/program/Program.h"

Program::Program(HardwareControl* control, IClient* client)
    : _control(control)
    , _client(client)
    , _currentActionIndex(0)
{
    // ...
}

void Program::Update()
{
    if (_currentAction != NULL)
    {
        _currentAction->Handle();

        if (_currentAction->IsDone())
        {
            SetNextAction();
        }
    }
}

void Program::SetNextAction()
{
    if (_currentActionIndex < _actions.size())
    {
        _currentAction = _actions[_currentActionIndex++];
    }
}

void Program::AddAction(IAction* action)
{
    action->SetHardwareControl(_control);
    action->SetClient(_client);

    _actions.push_back(action);
}
