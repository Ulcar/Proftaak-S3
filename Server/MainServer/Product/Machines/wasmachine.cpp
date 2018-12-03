#include "wasmachine.h"

Wasmachine::Wasmachine(std::string macAdress) :
    Machine(macAdress)
{
    
}

Wasmachine::~Wasmachine()
{
    
}


void Wasmachine::Beat()
{
    std::string message = socket->ReadLastMessage();
    if(message.empty())
    {
        return;
    }

    //handle message
}