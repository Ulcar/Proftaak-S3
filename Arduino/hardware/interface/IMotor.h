#ifndef IMOTOR_H
#define IMOTOR_H

enum MotorDirection
{
    MD_LEFT,
    MD_RIGHT
};

enum MotorSpeed
{
    SPEED_OFF,
    SPEED_LOW,
    SPEED_MEDIUM,
    SPEED_HIGH
};

class IMotor
{
public:
    virtual void SetDirection(MotorDirection direction) = 0;
    virtual void SetSpeed(MotorSpeed speed) = 0;
};

#endif
