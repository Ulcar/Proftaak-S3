#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <ArduinoSTL.h>

#include "IClient.h"

class SerialClient : public IClient
{
public:
    SerialClient(OnMessageReceivedCallback onMessageReceived);
    ~SerialClient();

    bool ConnectToServer(MachineType type);

    void SendMessage(MessageCode code);
    void SendMessage(MessageCode code, std::vector<String> parameters);

    std::vector<String> ReadMessage(bool shouldBlock = false);

    String GetMacAddress();

    bool IsConnectedToServer();

    void Update();

private:
    bool _isConnectedToServer;
    String _message;

    SerialClient(const SerialClient& other);
    SerialClient& operator=(const SerialClient& other);
};

#endif
