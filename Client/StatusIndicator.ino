#include "includes/hardware/StatusIndicator.h"

void StatusIndicator::Initialize()
{
    pinMode(OUTPUT_LED_RED, OUTPUT);
    pinMode(OUTPUT_LED_GREEN, OUTPUT);
    pinMode(OUTPUT_LED_BLUE, OUTPUT);
}

void StatusIndicator::SetStatus(Status status)
{
    _lightState = STATE_ON;
    _startMs = millis();
    _status = status;
}

void StatusIndicator::Update()
{
    switch (_status)
    {
    // Constant red light.
    case S_DECOUPLED:
        SetColor(255, 0, 0);
        break;

    // Blinking red light.
    case S_MALFUNCTION:
    {
        unsigned long currentMs = millis();

        if (currentMs - _startMs > BLINKING_DELAY)
        {
            _lightState = _lightState == STATE_ON ? STATE_OFF : STATE_ON;
            _startMs = currentMs;

            if (_lightState == STATE_ON)
            {
                SetColor(255, 0, 0);
            }
            else
            {
                SetColor(0, 0, 0);
            }
        }
        break;
    }

    // Constant orange light.
    case S_NO_POWER:
        SetColor(255, 35, 0);
        break;

    // Constant blue light.
    case S_NO_WATER:
        SetColor(0, 0, 255);
        break;

    // Constant green light.
    case S_DONE:
        SetColor(0, 255, 0);
        break;

    // Constant purple light.
    case S_BUSY:
        SetColor(255, 0, 255);
        break;

    default:
        // ...
        break;
    }
}

void StatusIndicator::SetColor(int red, int green, int blue)
{
    analogWrite(OUTPUT_LED_RED, red);
    analogWrite(OUTPUT_LED_GREEN, green);
    analogWrite(OUTPUT_LED_BLUE, blue);
}
