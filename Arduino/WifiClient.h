#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <WiFi.h>

#include "INetworkClient.h"

class WifiClient : public INetworkClient
{
public:
    WifiClient(String ssid, String ipAddress, int port);
    ~WifiClient();

    bool Connect();

    void SendMessage(String data);
    String ReadMessage();

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
