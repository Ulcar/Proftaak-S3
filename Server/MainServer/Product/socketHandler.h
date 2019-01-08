#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include "client.h"
#include "database.h"
#include "enums.h"
#include "logger.h"
#include "machine.h"
#include "socket.h"

#include <mutex>
#include <vector>

class SocketHandler
{
    public:
        static void RunSocketHandler(Database* tempdatabase);

    private:
        static Database* database;

        static void Setup(int *socketFd);
        static Client* CreateNewClient(char typeChar, std::string macAdress);
        static void ConnectClient(int socketFd);
        static bool ReadClient(Socket* socket);
};

#endif