#ifndef IMOTOR_H
#define IMOTOR_H

#include "ICentipedeShield.h"
#include "../../Enums.h"

class IMotor
{
public:
    virtual ~IMotor() = 0;

    virtual void Initialize(ICentipedeShield* centipede) = 0;

    virtual void SetDirection(MotorDirection direction) = 0;
    virtual void SetSpeed(MotorSpeed speed) = 0;

protected:
    ICentipedeShield* _centipede;
};

#endif
