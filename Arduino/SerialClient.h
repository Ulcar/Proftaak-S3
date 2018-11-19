#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include "INetworkClient.h"

class SerialClient : public INetworkClient
{
public:
    SerialClient();
    ~SerialClient();

    bool Connect();

    void SendMessage(String data);
    String ReadMessage();

    String GetMacAddress();
    bool IsConnected();
};

#endif
