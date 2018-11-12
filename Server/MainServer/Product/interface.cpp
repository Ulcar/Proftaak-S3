#include "interface.h"
#include "enums.h"


Interface::Interface(std::string macAdress)
    : macAdress(macAdress)
{
    error = Error::None;
}

Interface::~Interface()
{
    delete socket;
}

void Interface::Send(Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->QueSend(Protocol::ToClient(code, value));
}

void Interface::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete tempSocket;
    }
    socket = tempSocket;
}
