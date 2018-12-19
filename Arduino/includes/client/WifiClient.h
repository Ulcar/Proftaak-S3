#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <WiFi.h>

#include "../library/Vector.h"
#include "IClient.h"

class WifiClient : public IClient
{
public:
    WifiClient(String ssid, String ipAddress, int port);
    ~WifiClient();

    bool ConnectToServer(MachineType type);

    void SendMessage(Message code, String* parameters, int parameterCount);
    Vector<String>& ReadMessage(bool shouldBlock = false);

    String GetMacAddress();

    bool IsConnectedToServer()
    {
        return _isConnectedToServer;
    }

private:
    WiFiClient _client;

    String _ssid;
    String _ipAddress;

    bool _isConnectedToServer;

    int _status;
    int _port;

    bool IsConnectedToNetwork();
};

#endif
