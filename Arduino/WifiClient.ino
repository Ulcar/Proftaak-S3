#include "WifiClient.h"

WifiClient::WifiClient(String ssid, String ipAddress, int port)
    : _ssid(ssid)
    , _ipAddress(ipAddress)
    , _port(port)
    , _status(WL_IDLE_STATUS)
{
    _status = WiFi.begin(_ssid.c_str());
}

WifiClient::~WifiClient()
{
    if (_status == WL_CONNECTED)
    {
        _client.stop();
    }
}

bool WifiClient::Connect()
{
    if (!this->IsConnected())
    {
        return false;
    }

    return _client.connect(_ipAddress.c_str(), _port);
}

void WifiClient::SendMessage(String data)
{
    if (!this->IsConnected())
    {
        return;
    }

    _client.write(data.c_str());
}

String WifiClient::ReadMessage()
{
    if (!this->IsConnected())
    {
        return;
    }

    String message = "";

    while (_client.available())
    {
        message += (char) _client.read();
    }

    return message;
}

String WifiClient::GetMacAddress()
{
    String result;
    byte macAddress[6];
    char buffer[3];

    WiFi.macAddress(macAddress);

    for (int i = (sizeof(macAddress) / sizeof(macAddress[0])) - 1; i >= 0; --i)
    {
        sprintf(buffer, "%02X", macAddress[i]);

        result += String(buffer);
    }

    return String(result);
}

bool WifiClient::IsConnected()
{
    return _status == WL_CONNECTED;
}
