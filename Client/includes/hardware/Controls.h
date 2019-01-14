#ifndef CONTROLS_H
#define CONTROLS_H

#include "interface/IControls.h"

#define PIN_STROBE    (2)

#define PIN_DATA_A    (10)
#define PIN_DATA_B    (9)
#define PIN_DATA_C    (8)

#define PIN_GROUP_1   (1)
#define PIN_GROUP_2   (0)

#define OUTPUT_BUZZER (4)
#define OUTPUT_SOAP_1 (12)
#define OUTPUT_LOCK   (15)

class Controls : public IControls
{
public:
    Controls();
    ~Controls();

    void Initialize(ICentipedeShield* centipede);

    void SetLock(HardwareState state);
    void SetSoap(HardwareState state, int dispenser);
    void SetBuzzer(HardwareState state);

private:
    Controls(const Controls& other);
    Controls& operator=(const Controls& other);
};

#endif
