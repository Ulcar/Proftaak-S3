#include "laundryBasket.h"

void LaundryBasket::OnLaundryFinish(std::vector<Laundry*> &laundryToRemove)
{
    if(Tasks.size() <= 0)
    {
        done = true;
        return;
    }

    for(Laundry* laundry : LaundryVector)
    {
        laundry->TasksToDo.erase(laundry->TasksToDo.begin());
        //Check if clothing piece needs to do the next program, if not, return to database

        if(laundry->TasksToDo[0] != Tasks[0])
        {
            laundryToRemove.push_back(laundry);
        }
    }
}


bool LaundryBasket::AddLaundryToLaundryBasket(Laundry* laundry)
{
    if(currentWeight + laundry->GetWeight() > weightLimit)
    {
        return false;
    }

    LaundryVector.push_back(laundry);
    return true;
}

bool LaundryBasket::IsBusy()
{
    return busy;
}

LaundryBasket::LaundryBasket(std::vector<Type> machines)
{
    currentWeight = 0;
    weightLimit = MAX_WEIGHT;

    Tasks = machines;
    temperature = Temperature::Medium;
}

std::string LaundryBasket::GetMacAdress()
{
    return usedClientId;
}

bool LaundryBasket::GetDone()
{
    return done;
}

void LaundryBasket::SetBusy(bool busy)
{
    this->busy = busy;
}

Temperature LaundryBasket::GetTemperature()
{
    return temperature;
}