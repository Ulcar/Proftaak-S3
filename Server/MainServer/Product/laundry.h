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
        Temperature temperature;

        //weight in grams
        int GetWeight();
        void SetDone(bool done);
        bool GetDone();
        int GetID();
        void setID(int id);

    private:
        int weight;
        int id;
        bool done;
};

#endif


