#include "wasmachine.h"

Wasmachine::Wasmachine(int socketFd) :
    Machine(socketFd)
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
    if(Socket::Beat(readFds))
    {
        //handle Socket::GetPrevMessage()
    }
}