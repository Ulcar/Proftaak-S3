#include "wasmachine.h"

Wasmachine::Wasmachine(std::string macAdress) :
    Machine(macAdress)
{
    
}

Wasmachine::~Wasmachine()
{
    //call destructor Machine
}

void Wasmachine::RequestHeater(WasMachineHeater status)
{
    Machine::Send(CODE_HEATER, status);
}

void Wasmachine::Beat()
{
    if(socket->Beat())
    {
        //handle Socket::GetPrevMessage()
    }
}