#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <ArduinoSTL.h>
#include <WiFi.h>

#include "ITransport.h"

class WifiTransport : public ITransport
{
public:
    WifiTransport(String ssid, String password, String ipAddress, int port);
    ~WifiTransport();

    bool ConnectToServer();

    void Send(String data);
    String Read(bool shouldBlock = false);

    String GetMacAddress();

private:
    WiFiClient _client;

    String _message;
    String _ipAddress;

    int _status;
    int _port;

    WifiTransport(const WifiTransport& other);
    WifiTransport& operator=(const WifiTransport& other);

    bool IsConnectedToNetwork();
};

#endif
