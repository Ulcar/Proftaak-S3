#include "includes/client/SerialClient.h"

SerialClient::SerialClient()
{
    // ...
}

SerialClient::~SerialClient()
{
    // ...
}

bool SerialClient::ConnectToServer()
{
    return true;
}

void SerialClient::SendMessage(String data)
{
    if (!this->IsConnected())
    {
        return;
    }

    Serial.println(CLIENT_CHARACTER_START + data + CLIENT_CHARACTER_END);
}

String SerialClient::ReadMessage(bool shouldBlock = true)
{
    if (!this->IsConnected())
    {
        return;
    }

    String message = "";

    while (shouldBlock ? true : Serial.available())
    {
        if (Serial.available())
        {
            char character = Serial.read();

            if (character == SERVER_CHARACTER_START)
            {
                message = "";
            }
            else if (character == SERVER_CHARACTER_END)
            {
                break;
            }
            else
            {
                message += character;
            }
        }
    }

    return message;
}

String SerialClient::GetMacAddress()
{
    return "AABBCCDDEEFF";
}

bool SerialClient::IsConnected()
{
    return true;
}
