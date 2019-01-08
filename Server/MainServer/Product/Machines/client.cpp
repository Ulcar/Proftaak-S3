#include "client.h"

Client::Client(std::string macAdress, Type type)
    : macAdress(macAdress)
    , clientType(type)
{
    enabled = true;
    socket = nullptr;
}

Client::~Client()
{
    delete socket;
}

void Client::Send(CP_Code code, std::string value)
{
    std::vector<std::string> temp = {value};
    Send(code, temp);
}

void Client::Send(CP_Code code, std::vector<std::string> value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Translator::ToControlPanel(code, value));
}

void Client::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete socket;
    }
    socket = tempSocket;
}

bool Client::IsEnabled()
{
    return enabled;
}

void Client::SetEnable(bool enabled)
{
    Logger::Record(false, macAdress + " is now enabled: " + std::to_string(enabled), "client");
    this->enabled = enabled;
}