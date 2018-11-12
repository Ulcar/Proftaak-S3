#ifndef MACHINE_H
#define MACHINE_H

#include "socket.h"
#include "codes.h"
#include "protocol.h"

#include <cstring>

class Machine
{
    public:
        Machine(std::string macAdress);
        ~Machine();

        void Send(Code code, int value);
        virtual void Beat() = 0;
        Socket* socket;

    private:
        const std::string macAdress;
};

#endif