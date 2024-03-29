#include "laundryBasket.h"

void LaundryBasket::OnLaundryFinish(std::vector<Laundry*> &laundryToRemove)
{
    Tasks.erase(Tasks.begin());
    if(Tasks.size() <= 0)
    {
        done = true;
        for(Laundry* laundry : LaundryVector)
        {
            laundry->TasksToDo.erase(laundry->TasksToDo.begin());
            laundryToRemove.push_back(laundry);
            currentWeight -= laundry->GetWeight();

        }
    }

    else
    {
        for(Laundry* laundry : LaundryVector)
        {
            laundry->TasksToDo.erase(laundry->TasksToDo.begin());
            //Check if clothing piece needs to do the next program, if not, return to database

            if(laundry->TasksToDo[0] != Tasks[0])
            {
                laundryToRemove.push_back(laundry);
                currentWeight -= laundry->GetWeight();
            }
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
    currentWeight += laundry->GetWeight();
    return true;
}

bool LaundryBasket::IsBusy()
{
    return busy;
}

LaundryBasket::LaundryBasket(std::vector<Type> machines, Color color, Temperature temperature, int ID)
{
    currentWeight = 0;
    weightLimit = MAX_WEIGHT;
    this->color = color;
    Tasks = machines;
    this->temperature = temperature;
    this->ID = ID;
}

LaundryBasket::~LaundryBasket()
{
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

void LaundryBasket::SetMacAdress(std::string macAdress)
{
    usedClientId = macAdress;
}

Temperature LaundryBasket::GetTemperature()
{
    return temperature;
}

Color LaundryBasket::GetColor()
{
    return color;
}

int LaundryBasket::GetID()
{
    return ID;
}