#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include "IClient.h"

class SerialClient : public IClient
{
public:
    SerialClient();
    ~SerialClient();

    bool ConnectToServer();

    void SendMessage(String data);
    String ReadMessage(bool shouldBlock = true);

    String GetMacAddress();
    bool IsConnected();
};

#endif
