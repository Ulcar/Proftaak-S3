#ifndef IHARDWAREINTERFACE_H
#define IHARDWAREINTERFACE_H

#include <Centipede.h>

class IHardwareInterface
{
public:
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
