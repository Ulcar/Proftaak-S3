
#include "laundry.h"

int Laundry::GetWeight()
{
    return weight;
}

Laundry::Laundry(int weight)
{
    this->weight = weight;
    done = false;
}

bool Laundry::GetDone()
{
    return done;
}

void Laundry::SetDone(bool done)
{
    this->done = done;
}

int Laundry::GetID()
{
    return id;
}

void Laundry::setID(int id)
{
this->id = id;
}