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

void Database::AddCurrentPower(int addCurrentPower)
{
    if(addCurrentPower <= 0)
    {
        return;
    }
    std::unique_lock<std::mutex> lock (mtxPower);
    if(currentPower + addCurrentPower > MAXPOWER)
    {
        currentPower = MAXPOWER;
        return;
    }
    currentPower += addCurrentPower;
}

bool Database::RemoveCurrentPower(int removeCurrentPower)
{
    if(removeCurrentPower <= 0)
    {
        return false;
    }
    std::unique_lock<std::mutex> lock (mtxPower);
    if(currentPower - removeCurrentPower < 0)
    {
        currentPower = MAXPOWER;
        return false;
    }
    currentPower += removeCurrentPower;
    return true;
}

int Database::AskCurrentWater()
{
    std::unique_lock<std::mutex> lock (mtxWater);
    return currentWater;
}

void Database::AddCurrentWater(int addCurrentWater)
{
    if(addCurrentWater <= 0)
    {
        return;
    }
    std::unique_lock<std::mutex> lock (mtxWater);
    if(currentWater + addCurrentWater > MAXPOWER)
    {
        currentWater = MAXPOWER;
        return;
    }
    currentWater += addCurrentWater;
}

bool Database::RemoveCurrentWater(int removeCurrentWater)
{
    if(removeCurrentWater <= 0)
    {
        return false;
    }
    std::unique_lock<std::mutex> lock (mtxWater);
    if(currentWater - removeCurrentWater < 0)
    {
        currentWater = MAXPOWER;
        return false;
    }
    currentWater += removeCurrentWater;
    return true;
}

void Database::HandleWashFinish(std::string macAdress)
{
    std::vector<Was> wasToHandle;
    for (Wasbak was : wasbakken)
    {
        if(was.GetMacAdress() == macAdress)
        {
            was.OnWashFinish(wasToHandle);
        }
    }

    for(Was was : wasToHandle)
    {
        for(Wasbak bak : wasbakken)
        {
            if(!bak.IsBusy() && bak.tasks[0] == was.tasksToDo[0])
            {
                bak.AddWasToWasbak(was);
                return;
            }
        }

        Wasbak newWasbak = Wasbak(was.tasksToDo);
        wasbakken.push_back(newWasbak);
        
    }
}

void Database::HandleWash(std::vector<Was> washToHandle)
{
    bool found = false;
    for(Was was : washToHandle)
    {
        for(Wasbak bak : wasbakken)
        {
            if(!bak.IsBusy() && bak.tasks[0] == was.tasksToDo[0])
            {
                bak.AddWasToWasbak(was);
                found = true;
                break;
            }
        }

        if(!found)
        {
        Wasbak newWasbak = Wasbak(was.tasksToDo);
        wasbakken.push_back(newWasbak);
        }

       
        
    }
}

void Database::HandleLaundryBaskets()
{
    for(Wasbak bak : wasbakken)
    {
        if(!bak.IsBusy())
        {
            for(Client* client : clients)
            {
                if(bak.tasks[0] == client->GetType())
                {
                    //add checks to make sure machine isn't doing anything
                    // Do StartProgram on machine, and                 }
            }
        }
    }
}