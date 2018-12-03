#include "HardwareControl.h"
#include "hardware/interface/IWater.h"

#define OUTPUT_GROUP_2   ( 0)
#define OUTPUT_GROUP_1   ( 1)
#define OUTPUT_STROBE    ( 2)
#define OUTPUT_KEYSELECT ( 3)
#define OUTPUT_DATA_C    ( 8)
#define OUTPUT_DATA_B    ( 9)
#define OUTPUT_DATA_A    (10)

#define INPUT_IN_1       (22)
#define INPUT_IN_2       (21)
#define INPUT_IN_3       (20)

HardwareControl::HardwareControl(Centipede centipede, int interfaceCount)
    : _centipede(centipede)
{
    _interfaces = new IHardwareInterface*[interfaceCount];
}

void HardwareControl::Initialize()
{
    _centipede.initialize();

    for (int i = 0; i < 16; ++i)
    {
        _centipede.pinMode(i, OUTPUT);
    }

    _centipede.digitalWrite(OUTPUT_KEYSELECT, HIGH);
    _centipede.digitalWrite(OUTPUT_GROUP_2,   LOW);
    _centipede.digitalWrite(OUTPUT_GROUP_1,   LOW);
    _centipede.digitalWrite(OUTPUT_STROBE,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_C,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_B,    LOW);
    _centipede.digitalWrite(OUTPUT_DATA_A,    LOW);

    for (int i = 0; i < _interfaceCount; ++i)
    {
        _interfaces[i]->Initialize();
    }
}

void HardwareControl::AddInterface(IHardwareInterface* interface)
{
    interface->SetCentipede(_centipede);

    _interfaces[_interfaceCount++] = interface;
}

IHardwareInterface* HardwareControl::GetInterface(String name)
{
    for (int i = 0; i < _interfaceCount; ++i)
    {
        if (_interfaces[i]->GetName() == name)
        {
            return _interfaces[i];
        }
    }

    return NULL;
}
