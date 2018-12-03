#ifndef DATABASE_H
#define DATABASE_H

#include "client.h"
#include "socket.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <vector>

class Database
{
    public:
        Database();
        ~Database();
        std::vector<Client*> GetClients();
        void AddClient(Client* client);
        bool AskQuit();
        void SetQuit(bool quit);

    private:
        bool quit;
        std::vector<Client*> clients;

        std::mutex mtxClient;
        std::mutex mtxQuit;
};

#endif