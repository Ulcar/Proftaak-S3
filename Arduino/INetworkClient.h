#ifndef INETWORKCLIENT_H
#define INETWORKCLIENT_H

class INetworkClient
{
public:
    virtual bool Connect() = 0;

    virtual void SendMessage(String data) = 0;
    virtual String ReadMessage() = 0;

    virtual String GetMacAddress() = 0;
    virtual bool IsConnected() = 0;
};

#endif
