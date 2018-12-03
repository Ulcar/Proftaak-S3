#include "machine.h"
#include "enums.h"


Machine::Machine(std::string macAdress, Type type)
    : Client(macAdress, type)
{
    
}

Machine::~Machine()
{
    
}
