#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include "socket.h"
#include "debuglogger.h"
#include "errorlogger.h"
#include "machine.h"
#include "database.h"
#include "client.h"
#include "enums.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <unistd.h>
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