#ifndef MACHINE_H
#define MACHINE_H

#include "socket.h"
#include "codes.h"
#include "protocol.h"

#include <cstring>

class Machine
{
    public:
        Machine();
        ~Machine();

        void Send(Code code, int value);
        virtual void Beat(fd_set &readFds) = 0;
        Socket* socket;

    private:
        std::string macAdress;
};

#endif