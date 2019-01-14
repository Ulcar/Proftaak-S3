#include "includes/client/SerialTransport.h"

SerialTransport::SerialTransport()
{
    // ...
}

SerialTransport::~SerialTransport()
{
    // ...
}

bool SerialTransport::ConnectToServer()
{
    return false;
}

void SerialTransport::Send(String data)
{
    Serial.println(data);
}

String SerialTransport::Read(bool shouldBlock = false)
{
    while (shouldBlock || Serial.available())
    {
        if (Serial.available())
        {
            char character = (char) Serial.read();

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

String SerialTransport::GetMacAddress()
{
    return "AABBCCDDEEFF";
}
