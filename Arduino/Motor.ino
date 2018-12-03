#include "hardware/Motor.h"

void Motor::Initialize(Centipede centipede)
{
    _centipede = centipede;

    _centipede.digitalWrite(OUTPUT_MOTOR_DIRECTION, LOW);
    _centipede.digitalWrite(OUTPUT_SPEED_1, HIGH);
    _centipede.digitalWrite(OUTPUT_SPEED_2, HIGH);
}

void Motor::SetDirection(MotorDirection direction)
{
    _centipede.digitalWrite(OUTPUT_MOTOR_DIRECTION, (int) direction);
}

void Motor::SetSpeed(MotorSpeed speed)
{
    int speedValue = speed ^ 0x3;

    _centipede.digitalWrite(OUTPUT_SPEED_1, speedValue & 0x1);
    _centipede.digitalWrite(OUTPUT_SPEED_2, (speedValue >> 1) & 0x1);
}
