#include "includes/machine/Program.h"

Program::Program(int number)
    : _number(number)
{
    // ...
}

void Program::Update()
{
    _currentAction->Handle();

    if (_currentAction->IsDone())
    {
        GoToNextAction();
    }
}

void Program::GoToNextAction()
{
    if (_currentActionIndex < _actions.size())
    {
        _currentAction = _actions[_currentActionIndex++];
    }
}

int Program::GetNumber()
{
    return _number;
}

void Program::AddAction(IAction* action)
{
    _actions.push_back(action);
}
