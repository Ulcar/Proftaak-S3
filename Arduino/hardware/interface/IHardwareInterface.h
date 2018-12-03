#ifndef IHARDWAREINTERFACE_H
#define IHARDWAREINTERFACE_H

#include <Centipede.h>

enum HardwareState
{
    STATE_ON,
    STATE_OFF
};

class IHardwareInterface
{
public:
    virtual void Initialize() = 0;

    String GetName()
    {
        return this->_name;
    }

    void SetCentipede(Centipede centipede)
    {
        this->_centipede = centipede;
    }

protected:
    Centipede _centipede;
    String _name;
};

#endif
