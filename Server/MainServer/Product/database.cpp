#include "database.h"

Database::Database()
{
    quit = false;
    currentWater = 0;
    currentPower = 0;
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

std::vector<LaundryBasket*> Database::GetLaundryBaskets()
{
    std::unique_lock<std::mutex> lock (mtxLaundry);
    return laundryBaskets;
}

void Database::AddClient(Client* client)
{
    std::unique_lock<std::mutex> lock (mtxClient);
    clients.push_back(client);
}

void Database::AddLaundry(Laundry* laundry)
{
      std::unique_lock<std::mutex> lock (mtxLaundry);
      unhandledLaundry.push_back(laundry);
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

void Database::HandleLaundryFinish(std::string macAdress)
{
    std::vector<Laundry*> laundryToHandle;
    for (LaundryBasket* laundry : laundryBaskets)
    {
        if(laundry->GetMacAdress() == macAdress)
        {
            laundry->OnLaundryFinish(laundryToHandle);

            if(laundry->GetDone())
            {
                //do something when the Laundry is done!!!!!
            }
        }
    }

    for(Laundry* laundry : laundryToHandle)
    {
        for(LaundryBasket* bak : laundryBaskets)
        {
            if(!bak->IsBusy() && bak->Tasks[0] == laundry->TasksToDo[0])
            {
                bak->AddLaundryToLaundryBasket(laundry);
                return;
            }
        }

        LaundryBasket* newLaundryBasket = new LaundryBasket(laundry->TasksToDo);
        laundryBaskets.push_back(newLaundryBasket);
        
    }
}

void Database::HandleLaundry(std::vector<Laundry*>& laundryToHandle)
{
     std::unique_lock<std::mutex> lock (mtxLaundry);
     
    
    for(Laundry* laundry : laundryToHandle)
    {
        bool found = false;
         for(LaundryBasket* bak : laundryBaskets)
        {
            if(!bak->IsBusy() && (bak->Tasks[0] == laundry->TasksToDo[0]) && !bak->GetDone())
            {
                bak->AddLaundryToLaundryBasket(laundry);
                found = true;
                 Logger::Record(false, "Adding Laundry to Laundry Basket", "Database");
                break;
            }
        }

        if(!found)
        {
        LaundryBasket* newLaundryBasket = new LaundryBasket(laundry->TasksToDo);
        laundryBaskets.push_back(newLaundryBasket);
        newLaundryBasket->AddLaundryToLaundryBasket(laundry);

        Logger::Record(false, "Created new Laundry Basket", "Database");
        }

    }

    laundryToHandle.clear();


}

void Database::HandleLaundry()
{
   
    HandleLaundry(unhandledLaundry);
}

void Database::Update()
{
    
}

void Database::HandleLaundryBaskets()
{
    
    
     std::unique_lock<std::mutex> lock (mtxLaundry);
    for(LaundryBasket* bak : laundryBaskets)
    {
        if(!bak->IsBusy())
        {
            std::unique_lock<std::mutex> lock (mtxClient);
            for(Client* client : clients)
            {
                if(bak->Tasks[0] == client->GetType())
                {
                    if(Machine* machine = dynamic_cast<Machine*>(client))
                    {
                        //add checks to make sure machine isn't doing anything
                        if(!machine->IsInProgress() && !machine->IsRequestingInProgress() && machine->GetSocket() != nullptr)
                        {
                          
                            

                            switch(bak->GetTemperature())
                            {
                                case Cold:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_COLD);
                                machine->SetProgram(Program::PROGRAM_COLD);
                                break;

                                case Medium:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_WARM);
                                machine->SetProgram(Program::PROGRAM_WARM);
                                break;

                                case Hot:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_HOT);
                                machine->SetProgram(Program::PROGRAM_HOT);
                                break;
                            }
                            // Do StartProgram on machine, and set Inprogress if you get a response  
                            machine->SetRequestingInProgress(true);
                            bak->SetBusy(true);
                            break;

                        }
                    }
                    
                             
                }
            }
        }
    }
}