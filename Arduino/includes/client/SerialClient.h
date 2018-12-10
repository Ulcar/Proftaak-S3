#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include "IClient.h"

class SerialClient : public IClient
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
