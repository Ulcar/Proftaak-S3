#include "includes/program/Program.h"

Program::Program(int number, HardwareControl* control, IClient* client)
    : _currentAction(NULL)
    , _control(control)
    , _client(client)
    , _nextActionIndex(0)
    , _number(number)
{
    // ...
}

void Program::Start()
{
    _nextActionIndex = 0;
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
    if (_nextActionIndex < _actions.size())
    {
        _currentAction = _actions[_nextActionIndex++];

        return true;
    }

    // When the program is done we can unlock the door again.
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

void Program::AllowTakeWater()
{
    if (_currentAction != NULL)
    {
        _currentAction->AllowTakeWater();
    }
}

void Program::AllowHeatUp()
{
    if (_currentAction != NULL)
    {
        _currentAction->AllowHeatUp();
    }
}

int Program::GetNumber()
{
    return _number;
}
