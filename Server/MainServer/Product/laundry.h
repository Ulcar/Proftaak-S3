#ifndef LAUNDRY_H
#define LAUNDRY_H

#include "enums.h"

#include <vector>

class Laundry
{
    public:
        Laundry(int weight);

        Color ColorType;
        std::vector<Type> TasksToDo;

        //weight in grams
        int GetWeight();

    private:
        int weight;
};

#endif


