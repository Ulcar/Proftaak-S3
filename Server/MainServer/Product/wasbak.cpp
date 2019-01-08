#include "wasbak.h"

void Wasbak::OnWashFinish(std::vector<Was> &wasToRemove)
    {
       if(tasks.size() <= 0)
       {
           done = true;
           return;
       }
       for(Was was : wasVector)
       {
           was.tasksToDo.erase(was.tasksToDo.begin());
           //Check if clothing piece needs to do the next program, if not, return to database

           
           if(was.tasksToDo[0] != tasks[0])
           {
               wasToRemove.push_back(was);
           }
       }
    }


bool Wasbak::AddWasToWasbak(Was was)
{
    if(currentWeight + was.GetWeight() > weightLimit)
    {
        return false;
    }

    wasVector.push_back(was);
    return true;
}

bool Wasbak::IsBusy()
{
    return busy;
}

Wasbak::Wasbak(std::vector<Type> machines)
{
    currentWeight = 0;
    weightLimit = MAX_WEIGHT;

    tasks = machines;
    temperature = Temperature::Medium;
}

std::string Wasbak::GetMacAdress()
{
    return usedClientId;
}

bool Wasbak::GetDone()
{
    return done;
}

void Wasbak::SetBusy(bool busy)
{
    this->busy = busy;
}

Temperature Wasbak::GetTemperature()
{
    return temperature;
}