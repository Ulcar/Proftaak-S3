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

IAction* Program::CreateAction(int number, JsonObject& args)
{
    IAction* action = NULL;

    switch (number)
    {
    case A_SOAP:
    {
        int state = args["state"];
        int dispenser = args["dispenser"];

        action = new SoapAction(
            static_cast<HardwareState>(state),
            dispenser
        );

        break;
    }

    case A_BUZZER:
    {
        int state = args["state"];

        action = new BuzzerAction(
            static_cast<HardwareState>(state)
        );

        break;
    }

    case A_DRAIN_WATER:
    {
        action = new DrainWaterAction();

        break;
    }

    case A_HEAT:
    {
        int temp = args["temp"];

        action = new HeatAction(
            static_cast<Temperature>(temp)
        );

        break;
    }

    case A_FILL_WATER:
    {
        int level = args["level"];

        action = new FillWaterAction(
            static_cast<WaterLevel>(level)
        );

        break;
    }

    case A_REQUEST_POWER:
    {
        int power = args["power"];

        action = new RequestPowerAction(power);

        break;
    }

    case A_REQUEST_WATER:
    {
        int liters = args["liters"];

        action = new RequestPowerAction(liters);

        break;
    }

    case A_MOTOR_ROTATE:
    {
        int direction = args["direction"];
        int speed = args["speed"];

        action = new MotorRotateAction(
            static_cast<MotorDirection>(direction),
            static_cast<MotorSpeed>(speed)
        );

        break;
    }

    case A_DELAY:
    {
        unsigned long ms = args["ms"];

        action = new DelayAction(ms);

        break;
    }

    default:
        // ...
        break;
    }

    return action;
}


bool Program::Load(String json)
{
    DynamicJsonBuffer buffer(512);
    JsonObject& root = buffer.parseObject(json);

    if (!root.success())
    {
        Serial.println("Couldn't load the program.");
        return false;
    }

    int program = root["program"];

    SetNumber(program);

    for (JsonObject& elem : root["actions"].as<JsonArray>())
    {
        int nr = elem["action"];
        JsonObject& args = elem["args"];

        Serial.println("Loading action " + String(nr));

        IAction* action = CreateAction(nr, args);

        if (action != NULL)
        {
            AddAction(action);
        }
    }

    Serial.println("Loaded " + String(_actions.size()) + " programs.");

    return true;
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
