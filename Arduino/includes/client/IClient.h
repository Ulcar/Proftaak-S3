#ifndef ICLIENT_H
#define ICLIENT_H

#include <ArduinoSTL.h>

#include "../Enums.h"
#include "Protocol.h"

typedef void (*OnMessageReceivedCallback)(std::vector<String>);

class IClient
{
public:
    virtual bool ConnectToServer(MachineType type) = 0;

    virtual void SendMessage(Message code, String* parameters, int parameterCount) = 0;
    virtual std::vector<String> ReadMessage(bool shouldBlock = false) = 0;

    virtual String GetMacAddress() = 0;

    virtual bool IsConnectedToServer() = 0;
    virtual bool IsDataAvailable() = 0;

    virtual void Update() = 0;

    virtual void SetOnMessageReceived(OnMessageReceivedCallback callback)
    {
        _onMessageReceived = callback;
    }

protected:
    OnMessageReceivedCallback _onMessageReceived;
};

#endif
