#include "includes/client/SerialClient.h"

SerialClient::SerialClient()
    : _isConnectedToServer(false)
{
    // ...
}

SerialClient::~SerialClient()
{
    // ...
}

bool SerialClient::ConnectToServer(MachineType type)
{
    // Identify ourselves to the remote server as a washing machine.
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

void SerialClient::SendMessage(MessageCode code)
{
    SendMessage(code, { "" });
}

void SerialClient::SendMessage(MessageCode code, std::vector<String> parameters)
{
    Serial.println(Protocol::ToServer(code, parameters));
}

std::vector<String> SerialClient::ReadMessage(bool shouldBlock = false)
{
    String message = "";

    while (shouldBlock ? true : Serial.available())
    {
        if (Serial.available())
        {
            char character = Serial.read();

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

void SerialClient::Update()
{
    while (Serial.available())
    {
        char character = Serial.read();

        if (character == RECEIVE_START_CHARACTER)
        {
            _message = "";
        }
        else if (character == RECEIVE_END_CHARACTER)
        {
            if (_onMessageReceived != NULL)
            {
                _onMessageReceived(Protocol::FromServer(_message));
            }

            return;
        }
        else
        {
            _message += character;
        }
    }
}

String SerialClient::GetMacAddress()
{
    return "AABBCCDDEEFF";
}
