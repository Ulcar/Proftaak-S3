#include "machine.h"

Machine::Machine()
{
    
}

Machine::~Machine()
{
    //call destructor Socket
}

void Machine::Send(Code code, int value)
{
    Protocol::GetPort();
    int ff = code + value;
    std::cout << ff;
    //Socket::Send(Protocol::ToClient(code, value));
}