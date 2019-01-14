#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#ifdef __AVR__
#include <ArduinoSTL.h>
#endif

#include "../Enums.h"

class ITransport
{
public:
    virtual ~ITransport() { };

    virtual bool ConnectToServer() = 0;

    virtual void Send(String data) = 0;
    virtual String Read(bool shouldBlock = false) = 0;

    virtual String GetMacAddress() = 0;
};

#endif
