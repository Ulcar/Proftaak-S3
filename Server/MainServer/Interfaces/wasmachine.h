#ifndef WASMACHINE_H
#define WASMACHINE_H

#include "machine.h"
#include "wasmachineEnums.h"

class Wasmachine : public Machine
{
    public:
        Wasmachine(int socketFd);
        ~Wasmachine();

        void RequestHeater(WasMachineHeater status);
        void Beat(fd_set &readFds);

    private:
};

#endif