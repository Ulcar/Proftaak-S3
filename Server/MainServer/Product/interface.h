#ifndef INTERFACE_H
#define INTERFACE_H

#include "socket.h"
#include "protocol.h"

class Interface
{
    public:
        Interface(std::string macAdress);
        ~Interface();
        void Send(Code code, int value);
        void Read();
        int Ping();
        void Beat();
        void SetSocket(Socket* socket);

        Socket* GetSocket()
        {
            return socket;
        }

        std::string GetMacAdress()
        {
            return macAdress;
        }

    private:
        int error;
        const std::string macAdress;
        Socket* socket;
};

#endif