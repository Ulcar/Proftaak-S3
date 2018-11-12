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