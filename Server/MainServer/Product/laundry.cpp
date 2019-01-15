
#include "laundry.h"

int Laundry::GetWeight()
{
    return weight;
}

Laundry::Laundry(int weight, Temperature temperature, Color color)
{
    this->weight = weight;
    this->temperature = temperature;
    this->ColorType = color;
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

Temperature Laundry::GetTemperature()
{
    return temperature;
}

Color Laundry::GetColor()
{
    return ColorType;
}