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
        bool Beat();
        bool Read();
        void QueSend(std::string text);

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

        std::vector<std::string> bufferOut;
        std::vector<std::string> bufferIn;


    protected:
        void Send(std::string text);
};

#endif