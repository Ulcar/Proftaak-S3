#ifndef MOTOR_H
#define MOTOR_H

#include "interface/IHardwareInterface.h"
#include "interface/IMotor.h"

#define OUTPUT_MOTOR_DIRECTION (11)
#define OUTPUT_SPEED_1         ( 7)
#define OUTPUT_SPEED_2         ( 6)

class Motor : public IMotor, public IHardwareInterface
{
public:
    Motor();
    ~Motor();

    void Initialize();

    void SetDirection(MotorDirection direction);
    void SetSpeed(MotorSpeed speed);
};

#endif
