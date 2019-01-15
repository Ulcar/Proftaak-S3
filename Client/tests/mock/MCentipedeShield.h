#ifndef MCENTIPEDESHIELD_H
#define MCENTIPEDESHIELD_H

#include <gmock/gmock.h>

#include "includes/hardware/interface/ICentipedeShield.h"

class MCentipedeShield : public ICentipedeShield
{
public:
    MOCK_METHOD0(Initialize, void());
    MOCK_METHOD2(PinMode, void(int, int));
    MOCK_METHOD2(DigitalWrite, void(int, int));
    MOCK_METHOD1(DigitalRead, int(int));
};

#endif
