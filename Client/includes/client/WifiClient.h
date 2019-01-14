#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <ArduinoSTL.h>
#include <WiFi.h>

#include "IClient.h"

class WifiClient : public IClient
{
public:
    WifiClient(String ssid, String password, String ipAddress, int port, OnMessageReceivedCallback onMessageReceived);
    ~WifiClient();

    bool ConnectToServer(MachineType type);

    void SendMessage(MessageCode code);
    void SendMessage(MessageCode code, std::vector<String> parameters);

    std::vector<String> ReadMessage(bool shouldBlock = false);

    String GetMacAddress();

    bool IsConnectedToServer();

    void Update();

private:
    WiFiClient _client;

    String _message;
    String _ipAddress;

    bool _isConnectedToServer;

    int _status;
    int _port;

    WifiClient(const WifiClient& other);
    WifiClient& operator=(const WifiClient& other);

    bool IsConnectedToNetwork();
};

#endif
