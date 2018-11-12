#ifndef SOCKET_H
#define SOCKET_H

#include "codes.h"
#include "enums.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <vector>

class Socket
{
    public:
        Socket(int socketFd);
        ~Socket();
        int Ping();
        bool Beat(fd_set &readFds);
        std::string Read();

        int getSocketFd()
        {
            return socketFd;
        }
        std::string getPrevMessage()
        {
            return prevMessage;
        }

    private:
        int error;
        int ETA;
        int socketFd;
        bool waitingForClient;
        std::string prevMessage;

        std::vector<std::string> buffer;

        void QueSend(std::string text);

    protected:
        void Send(std::string text);
};

#endif