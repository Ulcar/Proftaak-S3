#include "includes/client/WifiTransport.h"

WifiTransport::WifiTransport(String ssid, String password, String ipAddress, int port)
    : _ipAddress(ipAddress)
    , _port(port)
{
    _status = WiFi.begin(ssid.c_str(), password.c_str());
}

WifiTransport::~WifiTransport()
{
    if (IsConnectedToNetwork())
    {
        _client.stop();
    }
}

bool WifiTransport::ConnectToServer()
{
    if (!IsConnectedToNetwork())
    {
        return false;
    }

    return _client.connect(_ipAddress.c_str(), _port);
}

void WifiTransport::Send(String data)
{
    if (!this->IsConnectedToNetwork())
    {
        return;
    }

    _client.write(data.c_str());
}

String WifiTransport::Read(bool shouldBlock = false)
{
    while (shouldBlock || _client.available())
    {
        if (_client.available())
        {
            char character = (char) _client.read();

            if (character == RECEIVE_START_CHARACTER)
            {
                _message = "";
            }
            else if (character == RECEIVE_END_CHARACTER)
            {
                return _message;
            }
            else
            {
                _message += character;
            }
        }
    }

    return "";
}

String WifiTransport::GetMacAddress()
{
    String result = "";

    byte macAddress[6];
    char buffer[3];

    WiFi.macAddress(macAddress);

    // Convert the MAC address to a hexadecimal string.
    for (int i = (sizeof(macAddress) / sizeof(macAddress[0])) - 1; i >= 0; --i)
    {
        sprintf(buffer, "%02X", macAddress[i]);

        result += String(buffer);
    }

    return result;
}

bool WifiTransport::IsConnectedToNetwork()
{
    return _status == WL_CONNECTED;
}
