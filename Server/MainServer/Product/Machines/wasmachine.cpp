#include "wasmachine.h"

Wasmachine::Wasmachine(std::string macAdress) :
    Machine(macAdress)
{
    
}

Wasmachine::~Wasmachine()
{
    
}

void Wasmachine::RequestHeater(WasMachineHeater status)
{
    Machine::Send(CODE_HEATER, status);
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