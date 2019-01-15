#ifndef MOTOR_H
#define MOTOR_H

#include "interface/IMotor.h"

#define OUTPUT_MOTOR_DIRECTION (11)
#define OUTPUT_SPEED_1         ( 7)
#define OUTPUT_SPEED_2         ( 6)

class Motor : public IMotor
{
public:
    Motor();
    ~Motor();

    void Initialize(ICentipedeShield* centipede);

    void SetDirection(MotorDirection direction);
    void SetSpeed(MotorSpeed speed);

private:
    Motor(const Motor& other);
    Motor& operator=(const Motor& other);
};

#endif
