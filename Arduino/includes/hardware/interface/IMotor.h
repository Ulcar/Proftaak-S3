#ifndef IMOTOR_H
#define IMOTOR_H

#include <Centipede.h>

#include "../Enums.h"

class IMotor
{
public:
    virtual void Initialize(Centipede centipede) = 0;

    virtual void SetDirection(MotorDirection direction) = 0;
    virtual void SetSpeed(MotorSpeed speed) = 0;

protected:
    Centipede _centipede;
};

#endif
