#include "HardwareControl.h"

void HardwareControl::AddInterface(IHardwareInterface* interface)
{
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
