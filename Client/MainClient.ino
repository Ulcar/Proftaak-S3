#include "includes/client/MainClient.h"

MainClient::MainClient(ITransport* transport, OnMessageReceivedCallback callback)
    : _callback(callback)
    , _transport(transport)
    , _isConnectedToServer(false)
{
    // ...
}

bool MainClient::ConnectToNetwork()
{
    return _transport->ConnectToNetwork();
}

bool MainClient::ConnectToServer(MachineType type)
{
    if (!_transport->ConnectToServer())
    {
        return false;
    }

    Send(M_CONNECT, { String(type), _transport->GetMacAddress() });

    // Read the response, if it's '0' the connection is accepted.
    std::vector<String> response = DecodeMessage(_transport->Read(true));

    if (response[0] == String(M_CONNECT) && response[1] == "0")
    {
        _isConnectedToServer = true;

        return true;
    }

    return false;
}

void MainClient::Send(MessageCode code, std::vector<String> parameters)
{
    String data = EncodeMessage(code, parameters);

// We only want to enable this Serial.println when compiling on the Arduino.
#ifdef __AVR__
    // Filter out the PING messages, because these are rather annoying due to
    // their frequency.
    if (code != M_PING)
    {
        Serial.println(" > Sending: " + data);
    }
#endif

    _transport->Send(data);
}

void MainClient::Update()
{
    String data = _transport->Read();

    if (data.length() > 0 && _callback != NULL)
    {
        std::vector<String> decoded = DecodeMessage(data);

// We only want to enable this Serial.println when compiling on the Arduino.
#ifdef __AVR__
        // Filter out the PING messages, because these are rather annoying due to
        // their frequency.
        if (decoded[0] != String(M_PING))
        {
            Serial.println(" < Received: " + data);
        }
#endif

        _callback(DecodeMessage(data));
    }
}

void MainClient::Reset()
{
    _isConnectedToServer = false;
}

bool MainClient::IsConnectedToNetwork()
{
    return _transport->IsConnectedToNetwork();
}

bool MainClient::IsConnectedToServer()
{
    return _isConnectedToServer;
}

String MainClient::EncodeMessage(MessageCode code, std::vector<String> parameters)
{
    String result = SEND_START_CHARACTER + String(code);

    for (int i = 0; i < parameters.size(); ++i)
    {
        if (parameters[i].length() > 0)
        {
            result += SEPARATOR_CHARACTER + parameters[i];
        }
    }

    result += SEND_END_CHARACTER;

    return result;
}

std::vector<String> MainClient::DecodeMessage(String message)
{
    // Make sure that there are no start and end characters.
    if (message[0] == RECEIVE_START_CHARACTER)
    {
        message = message.substring(1, message.length());
    }

    if (message[message.length() - 1] == RECEIVE_END_CHARACTER)
    {
        message = message.substring(0, message.length() - 1);
    }

    std::vector<String> command;
    size_t prevIndex = 0;

    while (true)
    {
        size_t index = message.indexOf(SEPARATOR_CHARACTER, prevIndex);

        // Test to see if there is only one part remaining. When there's only one
        // part remaining, the 'index' will be the maximum value of an integer.
        if (index > message.length())
        {
            command.push_back(message.substring(prevIndex, message.length()));

            break;
        }

        // Extract a part of the message.
        command.push_back(message.substring(prevIndex, index));

        prevIndex = index + 1;
    }

    return command;
}
