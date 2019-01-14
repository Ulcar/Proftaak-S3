#include "includes/client/WifiClient.h"

WifiClient::WifiClient(String ssid, String password, String ipAddress, int port, OnMessageReceivedCallback callback)
    : _ipAddress(ipAddress)
    , _port(port)
    , _isConnectedToServer(false)
{
    _onMessageReceived = callback;
    _status = WiFi.begin(ssid.c_str(), password.c_str());
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
    client->SendMessage(M_CONNECT, { String(type), this->GetMacAddress() });

    // Wait for the 'accept' response of the previous message.
    std::vector<String> response = this->ReadMessage(true);

    if (response[0] == String(M_CONNECT) && response[1] == "0")
    {
        _isConnectedToServer = true;

        return true;
    }

    return false;
}

void WifiClient::SendMessage(MessageCode code)
{
    SendMessage(code, { "" });
}

void WifiClient::SendMessage(MessageCode code, std::vector<String> parameters)
{
    if (!this->IsConnectedToNetwork())
    {
        return;
    }

    // Filter out the PING messages, because these are annoying due to their
    // frequency.
    if (code != M_PING)
    {
        Serial.println("Sending: " + Protocol::ToServer(code, parameters));
    }

    _client.write(Protocol::ToServer(code, parameters).c_str());
}

std::vector<String> WifiClient::ReadMessage(bool shouldBlock = false)
{
    if (!this->IsConnectedToNetwork())
    {
        return;
    }

    String message = "";

    while (shouldBlock || _client.available())
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

    std::vector<String> result = Protocol::FromServer(message);

    // Filter out the PING messages, because these are annoying due to their
    // frequency.
    if (result[0] != String(M_PING))
    {
        Serial.println("Received (blocking): " + message);
    }

    return result;
}

void WifiClient::Update()
{
    while (_client.available())
    {
        char character = _client.read();

        if (character == RECEIVE_START_CHARACTER)
        {
            _message = "";
        }
        else if (character == RECEIVE_END_CHARACTER)
        {
            if (_onMessageReceived != NULL)
            {
                std::vector<String> result = Protocol::FromServer(_message);

                if (result[0] != String(M_PING))
                {
                    Serial.println("Received (non-blocking): " + _message);
                }

                _onMessageReceived(result);
            }

            return;
        }
        else
        {
            _message += character;
        }
    }
}

String WifiClient::GetMacAddress()
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

bool WifiClient::IsConnectedToNetwork()
{
    return _status == WL_CONNECTED;
}

bool WifiClient::IsConnectedToServer()
{
    return _isConnectedToServer;
}
