#include "HardwareControl.h"

HardwareControl::HardwareControl(Centipede centipede)
    : _centipede(centipede)
{
    // ...
}

void HardwareControl::Initialize()
{
    _centipede.initialize();

    for (int i = 0; i <= 15; ++i)
    {
        _centipede.pinMode(i, OUTPUT);
    }
}

void HardwareControl::AddInterface(IHardwareInterface* interface)
{
    interface->SetCentipede(_centipede);

    _interfaces.push_back(interface);
}

IHardwareInterface* HardwareControl::GetInterface(String name)
{
    for (int i = 0; i < _interfaces.size(); ++i)
    {
        if (_interfaces[i]->GetName() == name)
        {
            return _interfaces[i];
        }
    }

    return NULL;
}
