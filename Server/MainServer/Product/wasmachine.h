#ifndef WASMACHINE_H
#define WASMACHINE_H

#include "machine.h"
#include "wasmachineEnums.h"
#include "iWasmachine.h"

class Wasmachine : public Machine , public iWasmachine
{
    public:
        Wasmachine(std::string macAdress);
        ~Wasmachine();

        void RequestHeater(WasMachineHeater status);
        void Beat();

    private:
};

#endif