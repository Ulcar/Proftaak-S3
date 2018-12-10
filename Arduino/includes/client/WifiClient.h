#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <WiFi.h>

#include "IClient.h"

class WifiClient : public IClient
{
public:
    WifiClient(String ssid, String ipAddress, int port);
    ~WifiClient();

    bool ConnectToServer();

    void SendMessage(String data);
    String ReadMessage(bool shouldBlock = true);

    String GetMacAddress();
    bool IsConnected();

private:
    WiFiClient _client;

    String _ssid;
    String _ipAddress;

    int _status;
    int _port;
};

#endif
