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
    if (this->IsConnectedToNetwork())
    {
        _client.stop();
    }
}

bool WifiClient::ConnectToServer(MachineType type)
{
    if (!this->IsConnectedToNetwork())
    {
        return false;
    }

    _client.connect(_ipAddress.c_str(), _port);


    // Identify ourselves to the remote server.
    String parameters[] = { String(type), this->GetMacAddress() };
    client->SendMessage(M_CONNECT, parameters, 2);

    // Wait for the 'accept' response of the previous message.
    Vector<String>& response = this->ReadMessage(true);

    if (response[0] == String(M_CONNECT) && response[1] == "0")
    {
        _isConnectedToServer = true;

        return true;
    }

    return false;
}

void WifiClient::SendMessage(Message code, String* parameters, int parameterCount)
{
    if (!this->IsConnectedToNetwork())
    {
        return;
    }

    Vector<String> parametersVector;

    for (int i = 0; i < parameterCount; ++i)
    {
        parametersVector.push_back(parameters[i]);
    }

    _client.write(Protocol::ToServer(code, parametersVector).c_str());
}

Vector<String>* WifiClient::ReadMessage(bool shouldBlock = false)
{
    if (!this->IsConnectedToNetwork())
    {
        return;
    }

    String message = "";

    while (shouldBlock ? true : _client.available())
    {
        if (_client.available())
        {
            char character = _client.read();

            if (character == RECEIVE_START_CHARACTER)
            {
                message = "";
            }
            else if (character == RECEIVE_END_CHARACTER)
            {
                break;
            }
            else
            {
                message += character;
            }
        }
    }

    return Protocol::FromServer(message);
}

String WifiClient::GetMacAddress()
{
    String result;
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

bool WifiClient::IsConnectedToNetwork()
{
    return _status == WL_CONNECTED;
}
