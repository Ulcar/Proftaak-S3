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

std::vector<Wasbak*> Database::GetWasbakken()
{
    std::unique_lock<std::mutex> lock (mtxWash);
    return wasbakken;
}

void Database::AddClient(Client* client)
{
    std::unique_lock<std::mutex> lock (mtxClient);
    clients.push_back(client);
}

void Database::AddWash(Was was)
{
      std::unique_lock<std::mutex> lock (mtxWash);
      unhandledWash.push_back(was);
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

void Database::HandleWashFinish(std::string macAdress)
{
    std::vector<Was> wasToHandle;
    for (Wasbak* was : wasbakken)
    {
        if(was->GetMacAdress() == macAdress)
        {
            was->OnWashFinish(wasToHandle);

            if(was->GetDone())
            {
                //do something when the wash is done!!!!!
            }
        }
    }

    for(Was was : wasToHandle)
    {
        for(Wasbak* bak : wasbakken)
        {
            if(!bak->IsBusy() && bak->tasks[0] == was.tasksToDo[0])
            {
                bak->AddWasToWasbak(was);
                return;
            }
        }

        Wasbak* newWasbak = new Wasbak(was.tasksToDo);
        wasbakken.push_back(newWasbak);
        
    }
}

void Database::HandleWash(std::vector<Was>& washToHandle)
{
     std::unique_lock<std::mutex> lock (mtxWash);
     
    
    for(Was was : washToHandle)
    {
        bool found = false;
         for(Wasbak* bak : wasbakken)
        {
            if(!bak->IsBusy() && (bak->tasks[0] == was.tasksToDo[0]) && !bak->GetDone())
            {
                bak->AddWasToWasbak(was);
                found = true;
                 Logger::Record(false, "Adding Laundry to Laundry Basket", "Database");
                break;
            }
        }

        if(!found)
        {
        Wasbak* newWasbak = new Wasbak(was.tasksToDo);
        wasbakken.push_back(newWasbak);
        newWasbak->AddWasToWasbak(was);

        Logger::Record(false, "Created new Laundry Basket", "Database");
        }

    }

    washToHandle.clear();


}

void Database::HandleWash()
{
   
    HandleWash(unhandledWash);
}

void Database::Update()
{
    
}

void Database::HandleLaundryBaskets()
{
    
    
     std::unique_lock<std::mutex> lock (mtxWash);
    for(Wasbak* bak : wasbakken)
    {
        if(!bak->IsBusy())
        {
            std::unique_lock<std::mutex> lock (mtxClient);
            for(Client* client : clients)
            {
                if(bak->tasks[0] == client->GetType())
                {
                    if(Machine* machine = dynamic_cast<Machine*>(client))
                    {
                        //add checks to make sure machine isn't doing anything
                        if(!machine->IsInProgress() && !machine->IsRequestingInProgress() && machine->GetSocket() != nullptr)
                        {
                          
                            

                            switch(bak->GetTemperature())
                            {
                                case Cold:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_XX);
                                machine->SetProgram(Program::PROGRAM_XX);
                                break;

                                case Medium:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_XX);
                                machine->SetProgram(Program::PROGRAM_XX);
                                break;

                                case Hot:
                                machine->Send(M_CODE_SENDPROGRAM, (int)Program::PROGRAM_XX);
                                machine->SetProgram(Program::PROGRAM_XX);
                                break;
                            }
                              // Do StartProgram on machine, and set Inprogress if you get a response  
                              machine->SetRequestingInProgress(true);
                              bak->SetBusy(true);

                        }
                    }
                    
                             
                }
            }
        }
    }
}