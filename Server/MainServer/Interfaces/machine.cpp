#include "machine.h"

Machine::Machine(std::string macAdress)
    : macAdress(macAdress)
{
    
}

Machine::~Machine()
{
    delete socket;
}

void Machine::Send(Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->QueSend(Protocol::ToClient(code, value));
}

void Machine::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete tempSocket;
    }
    socket = tempSocket;
}