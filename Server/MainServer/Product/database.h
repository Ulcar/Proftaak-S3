#ifndef DATABASE_H
#define DATABASE_H

#define MAXPOWER 1000
#define MAXWATER 1000

#include "client.h"
#include "socket.h"

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
        
        int AskCurrentWater();
        bool UpdateWater(int amountWater);
        void ResetWater(int amountWater);
        int AskCurrentPower();
        bool UpdatePower(int amountPower);
        void ResetPower(int amountPower);

    private:
        bool quit;
        std::vector<Client*> clients;

        std::mutex mtxClient;
        std::mutex mtxQuit;
        std::mutex mtxPower;
        std::mutex mtxWater;

        //Water is in Liters
        int currentWater;
        //power is in Watt
        int currentPower;
};

#endif