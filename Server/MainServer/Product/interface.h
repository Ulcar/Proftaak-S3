#ifndef INTERFACE_H
#define INTERFACE_H

#include "socket.h"

class Interface
{
    public:
        Interface(std::string macAdress);
        ~Interface();
        void Send();
        void Read();
        int Ping();
        Socket* socket;

    private:
        int error;
        std::string macAdress;
};

#endif