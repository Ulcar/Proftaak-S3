#ifndef MACHINE_H
#define MACHINE_H

#include "socket.h"
#include "codes.h"
#include "protocol.h"
#include "iMachine.h"

#include <cstring>

class Machine : public iMachine
{
    public:
        Machine(std::string macAdress);
        ~Machine();
        void Send(std::vector<std::string> message);

    protected:
        const std::string macAdress;
        Socket* socket;
};

#endif