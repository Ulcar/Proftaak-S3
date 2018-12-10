#include "client.h"

Client::Client(std::string macAdress, Type type)
    : macAdress(macAdress)
    , clientType(type)
{
    
}

Client::~Client()
{
    delete socket;
}

void Client::Send(CP_Code code, std::string value)
{
    Send(code, new std::vector(value));
}

void Client::Send(CP_Code code, std::vector<std::string> value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Protocol::ToControlPanel(code, value));
}

void Client::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete tempSocket;
    }
    socket = tempSocket;
}