#ifndef LAUNDRYBASKET_H
#define LAUNDRYBASKET_H

#include "enums.h"
#include "laundry.h"

#include <string>
#include <vector>

#define MAX_WEIGHT 5000

class LaundryBasket
{
    public:
        LaundryBasket(std::vector<Type> machines);
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
    

    private:
        std::string usedClientId;
        bool busy = false;
        bool done = false;

        //weight in grams
        int weightLimit;
        int currentWeight;

        Temperature temperature;
};


#endif