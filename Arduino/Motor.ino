#include "includes/hardware/Motor.h"

Motor::Motor()
{
    // ...
}

Motor::~Motor()
{
    // ...
}

void Motor::Initialize(ICentipedeShield* centipede)
{
    _centipede = centipede;

    _centipede->DigitalWrite(OUTPUT_MOTOR_DIRECTION, LOW);
    _centipede->DigitalWrite(OUTPUT_SPEED_1, HIGH);
    _centipede->DigitalWrite(OUTPUT_SPEED_2, HIGH);
}

void Motor::SetDirection(MotorDirection direction)
{
    _centipede->DigitalWrite(OUTPUT_MOTOR_DIRECTION, (int) direction);
}

void Motor::SetSpeed(MotorSpeed speed)
{
    int speedValue = speed ^ 0x3;

    _centipede->DigitalWrite(OUTPUT_SPEED_1, speedValue & 0x1);
    _centipede->DigitalWrite(OUTPUT_SPEED_2, (speedValue >> 1) & 0x1);
}
