#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <ArduinoSTL.h>

#include "IClient.h"

class SerialClient : public IClient
{
public:
    SerialClient();
    ~SerialClient();

    bool ConnectToServer(MachineType type);

    void SendMessage(MessageCode code);
    void SendMessage(MessageCode code, std::vector<String> parameters);

    std::vector<String> ReadMessage(bool shouldBlock = false);

    String GetMacAddress();

    bool IsConnectedToServer()
    {
        return _isConnectedToServer;
    }

    bool IsDataAvailable()
    {
        return Serial.available() > 0;
    }

    void Update();

private:
    bool _isConnectedToServer;
    String _message;
};

#endif
