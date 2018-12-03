#ifndef WASMACHINE_H
#define WASMACHINE_H

#include "machine.h"
#include "iWasmachine.h"

class Wasmachine : public Machine , public iWasmachine
{
    public:
        Wasmachine(std::string macAdress);
        ~Wasmachine();

        void Beat();

    private:
};

#endif