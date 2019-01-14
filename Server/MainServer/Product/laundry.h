#ifndef LAUNDRY_H
#define LAUNDRY_H

#include "enums.h"

#include <vector>

class Laundry
{
    public:
        Laundry(int weight, int id);

        Color ColorType;
        std::vector<Type> TasksToDo;

        //weight in grams
        int GetWeight();
        void SetDone(bool done);
        bool GetDone();

    private:
        int weight;
        int id;
        bool done;
};

#endif


