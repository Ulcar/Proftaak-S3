#include "wasbak.h"

void Wasbak::OnWashFinish(std::vector<Was> &wasToRemove)
    {
       wasVector.erase(wasVector.begin());
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
    currentWeight = MAX_WEIGHT;
    weightLimit = MAX_WEIGHT;

    tasks = machines;
}

std::string Wasbak::GetMacAdress()
{
    return usedClientId;
}