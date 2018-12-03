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

void Client::Send(Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Protocol::ToClient(code, value));
}

void Client::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete tempSocket;
    }
    socket = tempSocket;
}