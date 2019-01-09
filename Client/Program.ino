#include "includes/program/Program.h"

Program::Program(HardwareControl* control, IClient* client)
    : _currentAction(NULL)
    , _control(control)
    , _client(client)
    , _currentActionIndex(0)
{
    // ...
}

void Program::Start()
{
    _currentActionIndex = 0;
    _currentAction = NULL;
    _started = true;

    Controls* controls = _control->GetControls();
    controls->SetLock(STATE_ON);

    StatusIndicator* statusIndicator = _control->GetStatusIndicator();
    statusIndicator->SetStatus(S_BUSY);

    SetNextAction();
}

bool Program::Update()
{
    if (_started && _currentAction != NULL)
    {
        _currentAction->Handle();

        if (_currentAction->IsDone())
        {
            return SetNextAction();
        }
    }
}

bool Program::SetNextAction()
{
    if (_currentActionIndex < _actions.size())
    {
        _currentAction = _actions[_currentActionIndex++];

        return true;
    }

    _started = false;

    Controls* controls = _control->GetControls();
    controls->SetLock(STATE_OFF);

    return false;
}

void Program::AddAction(IAction* action)
{
    action->SetHardwareControl(_control);
    action->SetClient(_client);

    _actions.push_back(action);
}
