#ifndef SOCKET_H
#define SOCKET_H

#include "enums.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

class Socket
{
    public:
        Socket(int socketFd);
        ~Socket();
        void Send(std::string text);
        std::string Read();
        int Ping();
        int getSocketFd()
        {
            return socketFd;
        }

    private:
        int error;
        int ETA;
        int socketFd;
};

#endif