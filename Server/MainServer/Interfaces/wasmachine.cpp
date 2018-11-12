#include "wasmachine.h"

Wasmachine::Wasmachine() :
    Machine()
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

void Wasmachine::Beat(fd_set &readFds)
{
    if(socket->Beat(readFds))
    {
        //handle Socket::GetPrevMessage()
    }
}