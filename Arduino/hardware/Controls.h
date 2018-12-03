#ifndef CONTROLS_H
#define CONTROLS_H

#include "interface/IHardwareInterface.h"
#include "interface/IControls.h"

#define OUTPUT_BUZZER ( 4)
#define OUTPUT_SOAP_1 (12)
#define OUTPUT_LOCK   (15)

class Controls : public IControls, public IHardwareInterface
{
public:
    Controls();
    ~Controls();

    void Initialize();

    void SetLock(HardwareState state);
    void SetSoap(HardwareState state, int dispenser);
    void EnableBuzzer(int timeInMs);

private:
    int* _soapDispensers;
};

#endif
