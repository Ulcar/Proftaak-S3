#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include "../Enums.h"

class ITransport
{
public:
    virtual ~ITransport() { };

    virtual bool ConnectToNetwork() = 0;
    virtual bool ConnectToServer() = 0;

    virtual void Send(String data) = 0;
    virtual String Read(bool shouldBlock = false) = 0;

    virtual bool IsConnectedToNetwork() = 0;

    virtual String GetMacAddress() = 0;
};

#endif
