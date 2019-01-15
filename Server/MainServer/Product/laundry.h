#ifndef LAUNDRY_H
#define LAUNDRY_H

#include "enums.h"

#include <vector>

class Laundry
{
    public:
        Laundry(int weight, Temperature temperature, Color color);

        
        std::vector<Type> TasksToDo;

        //weight in grams
        int GetWeight();
        void SetDone(bool done);
        bool GetDone();
        int GetID();
        void setID(int id);

        Temperature GetTemperature();
        Color GetColor();

    private:
        int weight;
        int id;
        bool done;
        Temperature temperature;
        Color ColorType;
};

#endif


