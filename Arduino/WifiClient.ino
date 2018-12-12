#include "includes/client/WifiClient.h"

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

bool WifiClient::ConnectToServer()
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

    _client.write((SEND_CHARACTER_START + data + SEND_CHARACTER_END).c_str());
}

String WifiClient::ReadMessage(bool shouldBlock = true)
{
    if (!this->IsConnected())
    {
        return;
    }

    String message = "";

    while (shouldBlock ? true : _client.available())
    {
        if (_client.available())
        {
            char character = _client.read();

            if (character == RECEIVE_CHARACTER_START)
            {
                message = "";
            }
            else if (character == RECEIVE_CHARACTER_END)
            {
                message = "";
            }
            else
            {
                message += character;
            }
        }
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
