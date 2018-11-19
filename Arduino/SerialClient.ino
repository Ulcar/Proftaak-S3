#include "SerialClient.h"

SerialClient::SerialClient()
{
    // ...
}

SerialClient::~SerialClient()
{
    // ...
}

bool SerialClient::Connect()
{
    return true;
}

void SerialClient::SendMessage(String data)
{
    if (!this->IsConnected())
    {
        return;
    }

    Serial.println(data);
}

String SerialClient::ReadMessage()
{
    if (!this->IsConnected())
    {
        return;
    }

    String message = "";

    while (Serial.available())
    {
        message += (char) Serial.read();
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
