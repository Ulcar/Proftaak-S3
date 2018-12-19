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
    String parameters[] = { String(type), this->GetMacAddress() };
    client->SendMessage(M_CONNECT, parameters, 2);

    // Wait for the 'accept' response of the previous message.
    Vector<String>* response = this->ReadMessage(true);

    if (response[0] == String(M_CONNECT) && response[1] == "0")
    {
        _isConnectedToServer = true;

        return true;
    }

    return false;
}

void SerialClient::SendMessage(Message code, String* parameters, int parameterCount)
{
    Vector<String> parametersVector;

    for (int i = 0; i < parameterCount; ++i)
    {
        parametersVector.push_back(parameters[i]);
    }

    Serial.println(Protocol::ToServer(code, parametersVector));
}

Vector<String>* SerialClient::ReadMessage(bool shouldBlock = false)
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

String SerialClient::GetMacAddress()
{
    return "AABBCCDDEEFF";
}
