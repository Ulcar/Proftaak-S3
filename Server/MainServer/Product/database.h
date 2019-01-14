#ifndef DATABASE_H
#define DATABASE_H

#define MAXPOWER 1000
#define MAXWATER 1000

#include "client.h"
#include "machine.h"
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
        std::vector<LaundryBasket*> GetLaundryBaskets();
        void AddLaundry(Laundry* laundry);
        void AddClient(Client* client);
        bool AskQuit();
        void SetQuit(bool quit);
        
        int AskCurrentWater();
        bool UpdateWater(int amountWater);
        void ResetWater(int amountWater);
        int AskCurrentPower();
        bool UpdatePower(int amountPower);
        void ResetPower(int amountPower);

        void HandleLaundryFinish(std::string macAdress);
        void HandleLaundry(std::vector<Laundry*>& laundryToHandle);
        void HandleLaundry();
        void HandleLaundryBaskets();
        void Update();

    private:
        bool quit;
        std::vector<Client*> clients;
        std::vector<LaundryBasket*> laundryBaskets;
        std::vector<Laundry*> unhandledLaundry;

        std::mutex mtxClient;
        std::mutex mtxQuit;
        std::mutex mtxPower;
        std::mutex mtxWater;
        std::mutex mtxLaundry;

        //Water is in Liters
        int currentWater;
        //power is in Watt
        int currentPower;
        int laundryID;
};

#endif