#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include "IClient.h"

class SerialClient : public IClient
{
public:
    SerialClient();
    ~SerialClient();

    bool ConnectToServer(MachineType type);

    void SendMessage(Message code, String* parameters, int parameterCount);
    Vector<String>& ReadMessage(bool shouldBlock = false);

    String GetMacAddress();

    bool IsConnectedToServer()
    {
        return _isConnectedToServer;
    }

private:
    bool _isConnectedToServer;
};

#endif
