#ifndef SOCKET_H
#define SOCKET_H

#include "codes.h"
#include "enums.h"
#include "logger.h"

#include <arpa/inet.h>
#include <cstdio>
#include <mutex>
#include <unistd.h>
#include <vector>

class Socket
{
    public:
        Socket(int socketFd);
        virtual ~Socket();
        int Ping();
        void TrySend();
        bool Read();
        void NewSendMessage(std::string text);
        std::string ReadLastMessage();

        int GetSocketFd()
        {
            return socketFd;
        }

    private:
        //Copy disabled
        Socket(const Socket &other);
        Socket &operator = (const Socket &other);

        int ETA;
        int socketFd;
        bool waitingForClient;
        std::vector<std::string> bufferOut;
        std::vector<std::string> bufferIn;
        std::mutex mtxBufferIn;
        std::mutex mtxBufferOut;

        void AddMessageIn(std::string message);
        std::string GetMessageToSend();
        void Send(std::string text);
};

#endif