#ifndef LAUNDRY_BASKET_H
    #define LAUNDRY_BASKET_H
#include <string>
#include <vector>
#include "was.h"
#include "enums.h"

#define MAX_WEIGHT 5000

class Wasbak
{
    private:
    std::string usedClientId;
    bool busy = false;
    bool done = false;

    //weight in grams
    int weightLimit;
    int currentWeight;

    Temperature temperature;



   

    public:
    std::vector<Was*> wasVector;
    std::vector<Type> tasks;

    std::string GetMacAdress();

    
    
    bool IsBusy();
    void SetBusy(bool busy);    
    bool GetDone();

    int GetCurrentWeight();
    Wasbak(std::vector<Type> machines);

    void OnWashFinish(std::vector<Was*>& wasToRemove);
    bool AddWasToWasbak(Was* was);

    Temperature GetTemperature();
    void SetTemperature(Temperature temperature);
  


   

 

};


#endif