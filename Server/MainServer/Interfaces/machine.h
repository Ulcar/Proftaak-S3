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
        void SetSocket(Socket* socket);

        Socket* GetSocket()
        {
            return socket;
        }

        std::string GetMacAdress()
        {
            return macAdress;
        }

    protected:
        const std::string macAdress;
        Socket* socket;
};

#endif