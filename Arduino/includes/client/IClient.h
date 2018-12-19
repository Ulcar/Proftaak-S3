#ifndef ICLIENT_H
#define ICLIENT_H

#include "../library/Vector.h"
#include "../Enums.h"
#include "Protocol.h"

class IClient
{
public:
    virtual bool ConnectToServer(MachineType type) = 0;

    void SendMessage(Message code, String* parameters, int parameterCount);
    virtual Vector<String>& ReadMessage(bool shouldBlock = false) = 0;

    virtual String GetMacAddress() = 0;

    virtual bool IsConnectedToServer() = 0;
};

#endif
