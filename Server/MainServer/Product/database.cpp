#include "database.h"

Database::Database()
{
    quit = false;
}

Database::~Database()
{
    std::unique_lock<std::mutex> lock (mtxClient);

    for(Client* client : clients)
    {
        delete client;
    }
}

std::vector<Client*> Database::GetClients()
{
    std::unique_lock<std::mutex> lock (mtxClient);
    return clients;
}

void Database::AddClient(Client* client)
{
    std::unique_lock<std::mutex> lock (mtxClient);
    clients.push_back(client);
}

bool Database::AskQuit()
{
    std::unique_lock<std::mutex> lock (mtxQuit);
    return quit;
}

void Database::SetQuit(bool setQuit)
{
    std::unique_lock<std::mutex> lock (mtxQuit);
    quit = setQuit;
}

int Database::AskCurrentPower()
{
    std::unique_lock<std::mutex> lock (mtxPower);
    return currentPower;
}

void Database::ResetPower(int amountPower)
{
    if(amountPower <= 0)
    {
        return;
    }
    std::unique_lock<std::mutex> lock (mtxPower);
    if(currentPower + amountPower < 0)
    {
        currentPower = 0;
        return;
    }
    currentPower -= amountPower;
}

bool Database::UpdatePower(int amountPower)
{
    if(amountPower <= 0)
    {
        return false;
    }
    std::unique_lock<std::mutex> lock (mtxPower);
    if(currentPower + amountPower > MAXPOWER)
    {
        return false;
    }
    currentPower += amountPower;
    return true;
}

int Database::AskCurrentWater()
{
    std::unique_lock<std::mutex> lock (mtxWater);
    return currentWater;
}

void Database::ResetWater(int amountWater)
{
    if(amountWater <= 0)
    {
        return;
    }
    std::unique_lock<std::mutex> lock (mtxWater);
    if(currentWater + amountWater < 0)
    {
        currentWater = 0;
        return;
    }
    currentWater -= amountWater;
}

bool Database::UpdateWater(int amountWater)
{
    if(amountWater <= 0)
    {
        return false;
    }
    std::unique_lock<std::mutex> lock (mtxWater);
    if(currentWater + amountWater > MAXWATER)
    {
        return false;
    }
    currentWater += amountWater;
    return true;
}