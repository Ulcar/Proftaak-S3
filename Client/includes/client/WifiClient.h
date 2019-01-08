#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <ArduinoSTL.h>
#include <WiFi.h>

#include "IClient.h"

class WifiClient : public IClient
{
public:
    WifiClient(String ssid, String ipAddress, int port);
    ~WifiClient();

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
        return _client.available() > 0;
    }

    void Update();

private:
    WiFiClient _client;

    String _message;
    String _ssid;
    String _ipAddress;

    bool _isConnectedToServer;

    int _status;
    int _port;

    bool IsConnectedToNetwork();
};

#endif
