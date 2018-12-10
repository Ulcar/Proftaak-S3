#include "machine.h"
#include "enums.h"


Machine::Machine(std::string macAdress, Type type)
    : Client(macAdress, type)
{
    
}

Machine::~Machine()
{
    
}

void Machine::Send(M_Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Protocol::ToMachine(code, value));
}
