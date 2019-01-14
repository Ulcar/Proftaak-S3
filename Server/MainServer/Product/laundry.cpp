
#include "laundry.h"

int Laundry::GetWeight()
{
    return weight;
}

Laundry::Laundry(int weight, int id)
{
    this->weight = weight;
    this->id = id;
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
