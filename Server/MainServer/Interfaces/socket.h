#ifndef SOCKET_H
#define SOCKET_H

#include "codes.h"
#include "enums.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
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
        std::string ReadLastMessage();

        int getSocketFd()
        {
            return socketFd;
        }

    private:
        int error;
        int ETA;
        int socketFd;
        bool waitingForClient;
        std::vector<std::string> bufferOut;
        std::vector<std::string> bufferIn;
        std::mutex mtx;

        void AddMessageIn(std::string message);

    protected:
        void Send(std::string text);
};

#endif