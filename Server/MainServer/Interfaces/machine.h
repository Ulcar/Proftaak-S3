#ifndef MACHINE_H
#define MACHINE_H

#include "socket.h"
#include "codes.h"
#include "protocol.h"

#include <cstring>

class Machine : public Socket
{
    public:
        Machine(int socketFd);
        ~Machine();

        void Send(Code code, int value);
        virtual void Beat(fd_set &readFds) = 0;

    private:
};

#endif