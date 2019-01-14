#ifndef ICLIENT_H
#define ICLIENT_H

#ifdef __AVR__
#include <ArduinoSTL.h>
#endif

#include "../Enums.h"
#include "Protocol.h"

typedef void (*OnMessageReceivedCallback)(std::vector<String>);

class IClient
{
public:
    virtual ~IClient() { };

    virtual bool ConnectToServer(MachineType type) = 0;

    virtual void SendMessage(MessageCode code) = 0;
    virtual void SendMessage(MessageCode code, std::vector<String> parameters) = 0;

    virtual std::vector<String> ReadMessage(bool shouldBlock = false) = 0;

    virtual String GetMacAddress() = 0;

    virtual bool IsConnectedToServer() = 0;

    virtual void Update() = 0;

protected:
    OnMessageReceivedCallback _onMessageReceived;
};

#endif
