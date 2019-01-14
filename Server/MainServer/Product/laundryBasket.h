#ifndef LAUNDRYBASKET_H
#define LAUNDRYBASKET_H

#include "enums.h"
#include "laundry.h"

#include <string>
#include <vector>

#define MAX_WEIGHT 50

class LaundryBasket
{
    public:
        LaundryBasket(std::vector<Type> machines, Color color, Temperature temperature, int ID);
        ~LaundryBasket();

        void OnLaundryFinish(std::vector<Laundry*>& laundryToRemove);
        bool AddLaundryToLaundryBasket(Laundry* laundry);
        void SetTemperature(Temperature temperature);

        std::vector<Laundry*> LaundryVector;
        std::vector<Type> Tasks;

        std::string GetMacAdress();
        void SetMacAdress(std::string macAdress);

        bool IsBusy();
        void SetBusy(bool busy);    
        bool GetDone();

        int GetCurrentWeight();

        Temperature GetTemperature();

        Color GetColor();
        int GetID();
    

    private:
        std::string usedClientId;
        bool busy = false;
        bool done = false;

        //weight in grams
        int weightLimit;
        int currentWeight;
        int ID;

        Temperature temperature;
        Color color;
};


#endif