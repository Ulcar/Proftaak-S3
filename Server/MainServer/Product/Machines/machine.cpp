#include "machine.h"
#include "enums.h"


Machine::Machine(std::string macAdress, Type type)
    : Client(macAdress, type)
{
    
}

Machine::~Machine()
{
    
}

void Machine::Send(std::vector<std::string> message)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Protocol::ToInterface(message));
}
